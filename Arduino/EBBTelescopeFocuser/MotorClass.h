#include <EEPROM.h>;
#include <TMCStepper.h>
#include <limits.h>

#define D_STEP_PIN PD0
#define D_UART_PIN PA15
#define D_ENABLE_PIN PD2
#define D_HEATER_PIN PB13


class Motor: public TMC2209Stepper
{
   public:
      Motor(Stream * SerialPort, float RS, uint8_t addr);
      void Halt();
      void SetMoveTarget(long Position);
      boolean Move();
      void setHeaterPWM(byte HeaterValue);
      void engageMotor(boolean Engage);
      byte CurrentHeaterValue;
      boolean IsMoving;
      boolean IsEngaged;
      unsigned long CurrentPosition;
      unsigned long MoveTarget;
      boolean move_direction;
      int current;
      int steps;
      float max_rps;
};

Motor::Motor(Stream * SerialPort, float RS, uint8_t addr): TMC2209Stepper(SerialPort,  RS, addr) 
{
}

void Motor::Halt()
{
     IsMoving = false;
     EEPROM.put(1, CurrentPosition);
}

void Motor::setHeaterPWM(byte HeaterValue)
{
  analogWrite(D_HEATER_PIN, HeaterValue);
  CurrentHeaterValue = HeaterValue;
}

void Motor::engageMotor(boolean Engage)
{
  IsEngaged = Engage;
  if(Engage) {
    digitalWrite(D_ENABLE_PIN, LOW);
  }
  else {
    digitalWrite(D_ENABLE_PIN, HIGH);
  }
}
