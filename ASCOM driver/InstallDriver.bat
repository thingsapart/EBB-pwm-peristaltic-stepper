if not exist "C:\RealtaScopeTech\" mkdir C:\RealtaScopeTech

xcopy "%~dp0" C:\RealtaScopeTech /y

%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe /codebase "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll"
%SystemRoot%\Microsoft.NET\Framework64\v4.0.30319\regasm.exe /codebase "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll"

timeout 200