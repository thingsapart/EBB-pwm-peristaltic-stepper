# Arduino IDE firmware, C++

## Overview

The system incorporates a non-blocking serial port listener designed to await and process incoming commands efficiently. The commands are handled in a non blocking manner so that the motor's movements can be halted at any time. 

Leveraging the TMCStepper library by teemuatlut, our solution extends the base class and introduces methods for precise motor control and the regulation of the heater element. Custom methods have been developed to facilitate the reading of serial communications, parsing received text into discrete commands and parameters. These commands and parameters are then interpreted by the main system to execute the desired functions of the focuser with high precision and reliability.


## List of accepted commands

|Code|Description|Paramters required|Example|Return value|
|----|---------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------|---------------------|------------------------|
|G1|Sets maximum motor revolutions per second when PWM duty cycle is 100%, |Yes, float, number of revs/second |G1 4.0#|None|
|G2|Halt! Stops the focuser moving|No|G2#|None|
|G3|Returns true (1) or false (0) depending on if the motor is moving or not|No|G3#|"1" or "0"|
|G4|Returns the current maximum revs/second|No|G4#|long as string "4000"|
|G6|Sets motor current in milli amps|Yes interger|G6 500#|None|
|G7|Returns current motor current setting in milli amps|No|G7#|integer as string "500"|
|G8|Sets motor drivers number of micro steps|Yes, 0, 8, 16, 32, 64,128, 256|G8 16#|None|
|G9|Returns current number of micro steps|No|G9#|integer as string "36"|
|G10|Sets heater PWM value|Yes byte betwen 0 and 255|G10 128#|None|
|G11|Returns current heater PWM value|No|G11#|byte as string "255"|
|G12|Engage motor, true/false|Yes true "1" or false "0"|G12 1#|None|
|G13|Returns motor engaged state, true or false|No|G13#|"1" or "0"|
|G14|Resets saved settings to default|No|G14#|None|

## Future plans/changes

The code doesn't use any of the common C++ style naming conventions, its my first C++ program so only discovered them at the end of creating this project. For example some conventions use underscores in member names i.e. memberName_ is a private member of a class. 

There is also no error checking on the text being sent between the PC and the microcontroller, a simple checksum at the end would probably be good enough. Extremely long strings being sent over the serial connection can also lead to the microcontroller running out of RAM lol. 
