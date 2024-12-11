# Work in Progress!

# PWM-controlled peristaltic pump driver using a BTT EBB36, based on the [Realta Scope Tech EBBfocuser](https://github.com/RealtaScopeTech/Realta-EBBfocuser).

Connect a PWM output on your main device to a pin on the EBB36 to control a stepper motor (constant velocity only currently) - this is useful for example to control a stepper for a peristaltic pump using PWM. The default EBB36 input pin is PB9 in the middle of the Probe connector but this can be changed when compiling the firmware. The output PWM duty cycle on the main device determines the stepper's rotation speed and thus the pump output.

The maximum stepper revolutions/second and other settings are configurable both in the firmware and via [G-Codes](https://github.com/thingsapart/EBB-pwm-peristaltic-stepper/tree/main/Arduino#list-of-accepted-commands) if they are enabled at build time.

Works with eg:
* [Peristaltic Pump _ Nema 17 _ 608 Bearings](https://www.printables.com/model/910253-peristaltic-pump-_-nema-17-_-608-bearings/files) by ZRNNN, or 
* [Nema 17 Peristaltic Pump-608 Bearings-cooling water-engine oil-water](https://www.printables.com/model/974385-nema-17-peristaltic-pump-608-bearings-cooling-wate/files) by Michel.

# Why?

Klipper supports `[manual_stepper]` but Reprap Firmware does not. It is pretty easy to do PWM on RRF though, so this firmware along with an EBB36 allows one to control an external stepper motor. In this case used to drive a peristaltic pump via a Nema17 stepper, used as a pump for a minimum quantity lubrication system for a small CNC machine.

You can for example configure a 3.3V pin on your RRF board as a fan using the GCode command `M950 F10 C"<pin-id>" Q2000` (Fan 10, replace <pin-id> with your pin name) and then control the fan using Duet Web Control or using GCode - `M106 P10 S0.5 H-1` makes it run at 50% of the MOTOR_MAX_RPS setting (4 rev/sec per default, so 2 rps).

Defining the pin as a Gpio pin using `M950 P10 C"<pin-id>" Q2000` and `M42 P10 S0.5` would work the same if adding a fan to RRF and DWC is not desirable.

# EBB36 Focuser Housing

![EBB36 Focuser Case](Guide/Images/EBB36FinishedRCA.png)

-------------------


-------------------


# Original Documentation:


-------------------


## Realta Scope Tech EBBfocuser

![EBB36 Focuser Case](Guide/Images/EBB36FinishedRCA.png)

Welcome to the Realta EBBfocuser Project! This initiative is dedicated to creating a precise, customizable, and open-source focuser for telescopes. By leveraging the power of the maker community and freely available hardware, we've developed a solution that promotes collaboration and innovation.

## Project Overview

The heart of our project is the Bigtree Tech EBB36, a versatile stepper motor driver and microcontroller. This component is combined with a 3D printed case, custom firmware developed using the Arduino IDE, and a Windows driver built on the ASCOM framework. Together, these elements create a powerful and user-friendly telescope focuser designed for makers and enthusiasts who value customization and open-source principles.

## Key Components

**Bigtree Tech EBB36:** This stepper motor driver and microcontroller serves as the brain of our focuser, providing precise control over the telescope's focusing mechanism.

**3D Printed Case:** The case, designed to house the EBB36 and other components securely, can be easily printed using any standard 3D printer. It ensures the electronics are protected while maintaining accessibility for adjustments and upgrades.

**Arduino IDE Firmware:** Our custom firmware, developed in the Arduino IDE, allows for seamless communication between the EBB36 and the focusing mechanism. The firmware is open source, enabling users to modify and improve it according to their needs.

**ASCOM Framework Driver:** The ASCOM (Astronomy Common Object Model) framework driver ensures compatibility with a wide range of astronomy software, providing a standardized interface for controlling the focuser through a Windows environment.

## Features and Benefits

**Open Source:** All aspects of the Realta EBBfocuser, from the firmware to the case design, are open source. This allows users to freely modify, enhance, and share improvements, fostering a collaborative community.

**Maker-Centric Design:** The project is designed with makers in mind. Whether you enjoy 3D printing, coding, or electronics, the Realta EBBfocuser offers numerous opportunities to get hands-on and customize your setup.

**Precision:** The Bigtree Tech EBB36 offers high precision control, essential for achieving sharp focus in astrophotography and observation.

**Compatibility:** With the ASCOM driver, our focuser can be easily integrated with a wide array of existing astronomy software, enhancing its usability and versatility.
Getting Started

## To get started with the Realta EBBfocuser Project, you will need:

+ A Bigtree Tech EBB36 stepper motor driver and microcontroller
+ A 3D printer to print the custom-designed case
+ Basic electronics tools and components
+ The Arduino IDE for firmware installation and customization
+ A Windows PC for installing the ASCOM driver and controlling the focuser

We invite you to join our community, contribute to the project, and share your experiences. By working together, we can push the boundaries of what's possible in telescope focusing, making advanced astrophotography and observation more accessible to everyone.

The full guide to completing this project can be found here.

[Realta EBBfocuser complete guide](/Guide/ReadMe.md)
