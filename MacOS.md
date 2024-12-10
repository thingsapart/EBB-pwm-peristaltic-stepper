# Installation instructions without install STM32CubeProgrammer

1. Follow the regular guide, install Arduino (or VSCode - instructions missing)
2. Install dfu-util (`brew install dfu-util` once [homebrew is installed](https://www.brew.sh) )
3. Generate a binary
    1. Arduino IDE
        - "Menu" > "Sketch" > "Export Compiled Binary"
4. Flash BIN file
    1. Arduino IDE
        -  "Menu" > "Sketch" > "Show Sketch Folder"
        - navigate to shown folder in terminal (eg open Terminal, type `cd ` and drag and drop the folder icon from titlebar onto Terminal)
        - execute `dfu-util -a 0 -D ./EBBTelescopeFocuser/build/STMicroelectronics.stm32.3dprinter/EBBTelescopeFocuser.ino.bin -s 0x08000000:mass-erase:force:leave`

# List USB devices

- `system_profiler SPUSBDataType`
- FYI -- my EBB36 doesn't support proper USB3 USB-C cables - I have to connect a USB-C => USB3/2 hub and then use a USB2-to-USB-C cable.
