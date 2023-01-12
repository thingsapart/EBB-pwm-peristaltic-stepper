# Realta Scope Tech EBB42 telescope focuser

![EBB42 Focuser](Guide/Images/SideB.png)

![EBB42 Focuser](Guide/Images/SideA.png)

## Project goals.

+ Truley open source code i.e. do what you want with it.
+ Using open hardware only i.e. schematic available.
+ Firmware created using Arduino IDE with full guide to get it working with the EBB42.

## What you need to buy.

### Stepper motor

I have used a 23mm thick Nema 17 stepper motor like this 17HS4023. 

![Nema 17](Guide/Images/17HS4023.png)

However, any NEMA stepper motor thicker than this will work but you are limited to 1.5A per phase by the EBB42 stepper motor driver. Even thinner motors will work but you will have a hard time mounting them as the case will foul most mounting brackets. The FreeCAD file containing the parts is included in this repository so can be edited to provide a spacer to pad out the difference in width if needed. 

### BigTreeTech EBB42 

There are two versions of this, one with an accelerometer and one without, both will work but the accelerometer version is twice as expensive and no use of it is made in this project. 

![EBB42 Focuser PCB](Guide/Images/PCB.png)

### M3 Hex bolts

To secure the EBB42 you will need 4 12mm long M3 bolts while the ones for the stepper motor depend on how thick the one you buy is. The original bolts will not reach through the combined thickness of the case and motor so you will need 4 replacement ones. I found that for the 23mm thick motor I could use 22mm long bolts.  

### Optional: RCA connectors

If you want to use the dew heaters then you will need these RCA connectors.

![RCA Connector](Guide/Images/RCA_PANEL_MOUNT.png)

### Optional: Crimping tools and ferrules

The EBB42 focuser comes with all the accessories you need to connect it up it comes with the cable fittings needed to be added to wires to fit in its sockets and the metal pins too. However you will need to crimp these onto the wires yourself and a dupont compatable crimping tool greatly helps.

![Dupont crimping](Guide/Images/DuPontCrimping.png)

However it is possible to crimp using Needle Nose Pliers. 

[![Needle Nose Pliers](http://img.youtube.com/vi/JsoqBS1-k7M/0.jpg)](http://www.youtube.com/watch?v=JsoqBS1-k7M "Needle Nose Pliers")

I also made use of ferrules for terminating the dew heater wires used in the screw terminals.

![Dupont crimping](Guide/Images/FerruleCrimping.png)

## What you need to 3D print.

Only two parts need to be printed. Neither part requires supports and they were designed to be printed easily on a printer using an 0.8mm nozzle so should be easy prints on any printer using a smaller nozzle. 

![Printer](Guide/Images/PrintBed.png)

### Notes on filament type.

Stepper motors will get warm when opperating and even when not moving they are being held in place by powered magnetic fields. They are designed to cope with very very high temperatures. The firmware provided does make use of the TMC2209's CoolStep technology which greatly lowers the current drawn when not moving however the motor will still get warm to the touch, around 40c to 50c are common. This means you really should think twice about using a filament such as PLA which will start going floppy around this temperature. PETG would be better but ABS or ASA would be best. 

## Assembling the case.

![Exploded](Guide/Images/Exploded.png)

### Step 1: RCA Connectors (Optional)

If you plan on using the dew heater functionality you must fit them first as the EBB42 PCB will block access once its secured.

### Step 2: Attach stepper motor wires to EBB42 PCB

### Step 3: Fit EBB42 PCB

### Step 4: Secure base plate to case using 4 M3 12mm bolts.

### Step 5: Remove existing bolts from stepper motor

### Step 6: Attach stepper motor wires (if needed)

### Step 7: Secure motor to base plate using appropriate M3 bolts.

## Setting up the Ardunio IDE for use with EBB42.

### Install the Arduino IDE.

The latest Ardunio IDE can be found here.

https://www.arduino.cc/en/software

When you start the IDE for the first time you will be asked to allow it access to the internet, please allow it to do this as it will download various drivers and you will need this functionality later on to install some libaries. 

### User board manager to add stm32duino

Use the "tools" menu at the top to add the STM32 boards to the IDE.

![Board manager](Guide/Images/BoardsManager.png)

This opens a panel on the left hand side, in this search for "STM". 

![STM Search](Guide/Images/STMSearch.png)

Please note the version in the bottom left hand corner, if this is 2.4.0 or later then thats great however, if its not then 2.4.0 still hasn't been released and you will need to download the latest version from GitHub. 

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
11. Notes about INDI linux driver.
