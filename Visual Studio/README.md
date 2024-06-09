Todo: Blurb about what the visual studio code is.

# Overview of Visual Studio project

Todo: Blurb....including uses .net framework provided by ASCOM team, is VB.net, added custom options to settings menu and simply implemented serial send and recieves as required by ASCOM, note building on someone elses work.

# How to open and compile VS project.

In order to compile and use this code you need to have Visual Studio installed on your PC, the community edition works just fine for this.

https://visualstudio.microsoft.com/vs/community/

After that is installed you need to edit two of the downloaded files.

"%UserProfile%\Downloads\Realta-EBBfocuser-main\Realta-EBBfocuser-main\Visual Studio\EBB Focuser\Realta EBB Focuser\SetupDialogForm.resx"

and

"%UserProfile%\Downloads\Realta-EBBfocuser-main\Realta-EBBfocuser-main\Visual Studio\EBB Focuser\Realta EBB Focuser\My Project\Resources.resx"

For each of these files you need to right click on them, choose "properties" and tick the "Unblock" tick box in the bottom right. 

![Finally install the software](resx01.png)

Compiling this project in debug mode will create and register a COM object for windows/ASCOM to use. In order to do this Visual Studio needs to be run in Admin mode. To do this click on start menu and start typing "Visual", the icon for Visual studio should appear, right click on this and choose "Run as administrator".

![Run as Admin](RunAsAdmin.png)






