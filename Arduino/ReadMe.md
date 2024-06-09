# Arduino IDE firmware, C++

### Overview

No blocking serial port listener waiting for commands. Some of these commands required a stepper motor to move, this move is also handdled in a non blocking way which enables the motor to be halted while it is moving. List libraries it uses, give attribution to other open source library.

## List of accepted commands

|Code|Description|Paramters required|Example|Return value|
|----|---------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------|-------------|------------------------|
|G1|Sets target number of steps to move focuser to and will start the focuser moving.|Yes, long, number of steps |G1 4000#|None|
|G2|Halt! Stops the focuser moving|No|G2#|None|
|G3|Returns true (1) or false (0) depending on if the motor is moving or not|No|G3#|"1" or "0"|
|G4|Returns the current number of steps the focuser is currently at|No|G4#|long as string "4000"|
|G5|Changes the current number of steps without moving|Yes, long, number of steps |G5 4000#|None|
|G6|Sets motor current in micro amps|Yes interger|G6 500#|None|
|G7|Returns current motor current setting in micro amps|No|G7#|interger as string "500"|
|G8|Sets motor drivers number of micro steps|Yes, 0, 8, 16, 32, 64,128, 256|G8 16#|None|
|G9|Returns current number of micro steps|No|G9#|integer as string "36"|
|G10|Sets heater PWM value|Yes byte betwen 0 and 255|G10 128#|None|
|G11|Returns current heater PWM value|No|G11#|byte as string "255"|
|G12|Engage motor, true/false|Yes true "1" or false "0"|G12 1#|None|
|G13|Returns motor engaged state, true or false|No|G13#|"1" or "0"|
|G14|Resets saved settings to default, current position to 50,000, motor current to 500 micro amps and microsteps to 8|No|G14#|None|
