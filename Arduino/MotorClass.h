#include <EEPROM.h>;
#include <TMCStepper.h>

/*
 * 
 * "Halt"
 * "IsMoving" get true or false
 * "Move" pass integer of where you want it to move to
 * "Position" returns focuser current position
 * 
 */

class Motor: public TMC2209Stepper
{
   public:
      Motor(Stream * SerialPort, float RS, uint8_t addr);
      void Halt();
      void SetMoveTarget(long Position);
      boolean Move();
      boolean IsMoving;
      long CurrentPosition;
      long MoveTarget;
      boolean move_direction;
      int current;
      int steps;
};

Motor::Motor(Stream * SerialPort, float RS, uint8_t addr): TMC2209Stepper(SerialPort,  RS, addr) 
{
}



void Motor::Halt()
{
     IsMoving = false;
     EEPROM.put(1, CurrentPosition);
}

void Motor::SetMoveTarget(long Position)
{
  if(CurrentPosition != Position)
  {
     IsMoving = true;
     MoveTarget = Position;
  }
}

boolean Motor::Move()
{
          long difference;
          boolean new_direction;
          difference = MoveTarget - CurrentPosition;
          if(difference == 0)
          {
            Halt();
            return false;
          }
          else
          {
            if(difference > 0)
            {
              new_direction = true;
              CurrentPosition = CurrentPosition + 1;
            }
            else
            {
              new_direction = false;
              CurrentPosition = CurrentPosition - 1;
            }

            if(new_direction != move_direction)
            {
              move_direction = new_direction;
              shaft(move_direction);   
            }
            
            digitalWrite(PD0, HIGH); // Raise voltage on this pin to VCC or 3.3v
            delayMicroseconds(75); // wait
            digitalWrite(PD0, LOW);
            delayMicroseconds(75); // wait

            return true;
            
          }
}
