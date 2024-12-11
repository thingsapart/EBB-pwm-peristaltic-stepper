Pre-compiled firmware built using the Arduino IDE.

Serial-G-Code interface and EEPROM are enabled (but EEPROM has not been tested currently).

Can be flashed using DFUUtil on MacOS and Linux, adjust the following to your download location:

```dfu-util -a 0 -D ~/Downloads/EBBTelescopeFocuser.ino.bin -s 0x08000000:mass-erase:force:leave```
