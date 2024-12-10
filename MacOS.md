# Installation instructions without install STM32CubeProgrammer

1. Follow the regular guide, install Arduino (or VSCode - instructions missing)
2. Generate a binary
  1. Arduino IDE
    1. "Menu" > "Sketch" > "Export Compiled Binary"
3. Flash BIN file
  1. Arduino IDE
    2.  "Menu" > "Sketch" > "Show Sketch Folder"
    3. navigate to shown folder in terminal (eg open Terminal, type `cd ` and drag and drop the folder icon from titlebar onto Terminal)
    4. execute `dfu-util -a 0 -D ./EBBTelescopeFocuser/build/STMicroelectronics.stm32.3dprinter/EBBTelescopeFocuser.ino.bin -s 0x08000000:mass-erase:force:leave`

# List USB devices

`system_profiler SPUSBDataType`
