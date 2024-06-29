if not exist "C:\RealtaScopeTech\" mkdir C:\RealtaScopeTech

xcopy "%~dp0" C:\RealtaScopeTech /y

%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe /codebase "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll" runhidden 32bit
%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe /codebase "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll" runhidden 64bit

timeout 200