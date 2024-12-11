#define FLASH_BANK_NUMBER FLASH_BANK_1

#include <EEPROM.h>;
#include <SoftwareSerial.h>
#include "MotorClass.h";
#include "SerialComms.h";

// PINS: Motor.
#define D_STEP_PIN PD0
#define D_UART_PIN PA15
#define D_ENABLE_PIN PD2
#define D_DIR_PIN PD1

// PINS: PWM input (PB9 on aux plug eg).
#define D_PWM_INPUT_PIN PB9

// CONFIG: board/hardware.
#define D_DRIVER_ADDRESS 0b00         // PCB has both TMC2209 MS1 and MS2 pins grounded so this is the correct address for that configuration
#define D_R_SENSE 0.11f               // These are the resistance values of the current monitoring resistors as per the PCB datasheet, it has two 0R11 resistors (0.11 Ohm). This is used by the TMC2209 stepper driver to measure the current going to the stepper motor. It has one resistor for each coil of the stepper. 
 
// SETUP:
#define MOTOR_CURRENT 1000
#define MOTOR_MAX_RPS 4.0f            // Motor revolutions per second of the motor, float.
#define MOTOR_STEPS_PER_REV 200       // Motor full steps per revolution (= 360 / motor-degrees-per-step), 1.8* ~ 200, 0.9* ~ 400.
#define MOTOR_MICROSTEPS 16           // Default microsteps, can be overridden if serial G-Codes and EEPROM are enabled.

#define MOTOR_DIRECTION LOW           // flip value to HIGH/LOW to reverse motor direction, direction depends on motor wiring.

// CONFIG: Features.
// #define DEBUG                      // Debug output on serial port.
#define SERIAL_GCODE                  // G-Code config inherited from Realta Ebb Telescope Focuser - allows setting current and other useful features but requires EEPROM.
// #define EEPROM                     // Needs modification of board config to allow enabling the feature.

SoftwareSerial G_TMC_SERIAL (D_UART_PIN, D_UART_PIN);
Motor MyMotor(&G_TMC_SERIAL, D_R_SENSE, D_DRIVER_ADDRESS);

const unsigned long TIMEOUT = 1000; // 1 millisecond (100 Hz) 

// https://forum.arduino.cc/t/to-read-pwm-signal-with-pulsein/930016/5
int readPWM(int pin)
{
  unsigned long highDuration = pulseIn(pin, HIGH, TIMEOUT); 
  unsigned long lowDuration = pulseIn(pin, LOW, TIMEOUT);

#if DEBUG
  Serial.print(highDuration);
  Serial.print(", ");
  Serial.print(lowDuration);
  Serial.println(" -> ");
#endif

  if (highDuration == 0 || lowDuration == 0)
    return digitalRead(pin) == HIGH ? 255 : 0;

  return (highDuration * 255) / (highDuration + lowDuration);
}

// Current version of settings, change whenever slots change or setting is added.
#define SETTINGS_VER 9 

void reset_eeprom_to_defaults () {
  EEPROM.put(1, 0); // Current position.
  EEPROM.put(10, MOTOR_CURRENT); // Motor Current.
  EEPROM.put(20, MOTOR_MICROSTEPS); // Micro Steps.
  EEPROM.put(30, MOTOR_MAX_RPS); // Default max rps.
  EEPROM.put(0, SETTINGS_VER); 
}

void setup() {
#if defined(EEPROM) && defined(FLASH_BANK_NUMBER)
  // put your setup code here, to run once:
  byte isFirstRun;
  EEPROM.get(0, isFirstRun);

  if (isFirstRun != SETTINGS_VER) {
    reset_eeprom_to_defaults();
  }
  
  // Apply values from EEPROM.
  EEPROM.get(1, MyMotor.CurrentPosition);
  EEPROM.get(10, MyMotor.current);
  EEPROM.get(20, MyMotor.steps);
  EEPROM.get(30, MyMotor.max_rps);
#else
  MyMotor.steps = MOTOR_MICROSTEPS;
  MyMotor.current = MOTOR_CURRENT;
  MyMotor.CurrentPosition = 0;
  MyMotor.max_rps = MOTOR_MAX_RPS;
#endif

  MyMotor.IsMoving = false;
  pinMode(D_STEP_PIN, OUTPUT);
  pinMode(D_ENABLE_PIN, OUTPUT);
  pinMode(D_DIR_PIN, OUTPUT);

  // Sanity check current values and reset to default if out of range.
  if (MyMotor.current < 200 || MyMotor.current > 1500) { MyMotor.current = MOTOR_CURRENT; }

  MyMotor.engageMotor(true);
  MyMotor.setHeaterPWM(0);
  
  // Start serial communication to PC.
  Serial.begin(9600);
  Serial.println("Serial started");

  // Set up PWM input pin.
  pinMode(D_PWM_INPUT_PIN, INPUT);

  // LED.
  pinMode(LED_BUILTIN, OUTPUT);

  // Start serial communication with TMC.
  G_TMC_SERIAL.begin(11520);
  MyMotor.beginSerial(11520); 
  MyMotor.begin();                                                                                                                                                                                                                                                                                                                            // UART: Init SW UART (if selected) with default 115200 baudrate
  MyMotor.toff(5);                          // Enables driver in software
  MyMotor.rms_current(MyMotor.current);     // Set motor RMS current, needs to be user configurable, unit is mA
  MyMotor.microsteps(MyMotor.steps);        // Set the micro steps of the motor driver

  MyMotor.en_spreadCycle(true);             // sets stepper to use spreadcycle mode for more torque.
  // MyMotor.pwm_autoscale(true);           // Needed for stealthChop

  // Set direction.
  digitalWrite(D_DIR_PIN, MOTOR_DIRECTION);
}

void loop() {
  int duty_cycle = readPWM(D_PWM_INPUT_PIN);

  if (duty_cycle > 0) {
    // Compute motor velocity from PWM duty_cycle, steps per revolution, microsteps and maximum motor revs/sec.
    MyMotor.VACTUAL((float) duty_cycle / 255.0f / 0.715f * MOTOR_STEPS_PER_REV * MyMotor.steps * MyMotor.max_rps);
  } else {
    MyMotor.engageMotor(false);
  }

#ifdef DEBUG  
  Serial.print("duty cycle: ");
  Serial.println(duty_cycle);
#endif

#ifdef SERIAL_GCODE
   // Check the serial port for command
   P_PROCESS_SERIAL_PORT();

   // If we got a command then split into G code and parameters
   if (G_SERIAL_LINE_FEED_RECEIVED)
   {
     P_SPLIT_G_CODE_AND_PARAMS();
   }

    // Now process G code
   if (G_END_COMMAND_FOUND)
   {
      G_END_COMMAND_FOUND = false;

      // G1: Set Motor max RPS.
      if(G_COMMAND == "G1")
      {
        MyMotor.max_rps = G_PARAMS.toFloat();
      }
      // G2: Halt motor.
      if(G_COMMAND == "G2")
      {
        MyMotor.Halt();
      }
      // G3: Returns true (1) or false (0) depending on if the motor is moving or not.
      if(G_COMMAND == "G3")
      {
        Serial.print(String(MyMotor.IsMoving) + "#");
      }
      // G4: Returns the current maximum revs/second.
      if(G_COMMAND == "G4")
      {
        Serial.print(String(MyMotor.max_rps) + "#");
      }
      // G6: Sets motor current in milli amps.
      if(G_COMMAND == "G6")
      {
        MyMotor.current = G_PARAMS.toInt();
        EEPROM.put(10,MyMotor.current);
        MyMotor.rms_current(MyMotor.current);
      }
      // G7: Returns current motor current setting in milli amps.
      if(G_COMMAND == "G7")
      {
        Serial.print(String(MyMotor.current) + "#");
      }
      // G8: Sets motor drivers number of micro steps: 0, 8, 16, 32, 64,128, 256.
      if(G_COMMAND == "G8")
      {
        if(G_HAS_PARAMS)
        {
          MyMotor.steps = G_PARAMS.toInt();
          EEPROM.put(20, MyMotor.steps);
          MyMotor.microsteps(MyMotor.steps);
        }
      }
      // G9: Returns current number of micro steps.
      if(G_COMMAND == "G9")
      {
        Serial.print(String(MyMotor.steps) + "#");
      }
      // G10: Sets heater PWM value.
      if(G_COMMAND == "G10")
      {
        MyMotor.setHeaterPWM(G_PARAMS.toInt());
      }
      // G11: Returns current heater PWM value.
      if(G_COMMAND == "G11")
      {
        Serial.print(String(MyMotor.CurrentHeaterValue) + "#");     
      }
      // G12: Engage motor, true/false.
      if(G_COMMAND == "G12")
      {
        boolean trueFalse;
        if( G_PARAMS == "1")
        {
          trueFalse = true;
        }
        else
        {
          trueFalse = false;
        }
        
        MyMotor.engageMotor(trueFalse);
      }
      // G13: Returns motor engaged state, true or false.
      if(G_COMMAND == "G13")
      {
        if(MyMotor.IsEngaged)
        {
          Serial.print("1#");
        }
        else
        {
          Serial.print("0#");
        }
      }
      // G14: Resets saved settings to default.
      if(G_COMMAND == "G14")
      {
        // send some of these settings to the motor driver
        MyMotor.rms_current(MyMotor.current);     // Set motor RMS current, needs to be user configurable, unit is mA
        MyMotor.microsteps(MyMotor.steps);  // Set the micro steps of the motor driver
      }
   }
#endif 
}
