# Realta Scope Tech EBB42 telescope focuser (version 1.2).

![EBB42 Focuser](Images/Guide/PCB.png)

## Project goals.

+ Truley open source code i.e. do what you want with it.
+ Using open hardware only i.e. schematic available.
+ Firmware created using Arduino IDE with full guide to get it working with the EBB42.

## Sections in this document

Setting up the Ardunio IDE for use with EBB42.
1. Install Ardunio IDE
2. User board manager to add stm32duino
  If still version 2.3.0 then extra steps
   1. Install GIT
   2. Go to folder. "%LocalAppData%\Arduino15\packages\STMicroelectronics\hardware\stm32"
   3. Delete file named "2.3.0"
   4. git clone https://github.com/stm32duino/Arduino_Core_STM32.git 2.3.0
3. Adding in required linbraries.
4. Install STM32cube
5. Adding in required linbraries.
6. Compiling and uploading source files using Ardunio IDE.
7. Alternatively uploading pre-compiled binaries using STMCubeProgrammer software.
8. Compiling ASCOM driver from source code.
9. Alternatively using pre-compiled ASCOM driver installer.
10. How to use ASCOM driver (Using N.I.N.A).
11. Notes about INDI linus driver.
