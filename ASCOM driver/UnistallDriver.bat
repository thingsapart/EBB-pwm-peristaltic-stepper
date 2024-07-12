%SystemRoot%\Microsoft.NET\Framework64\v4.0.30319\regasm.exe -u "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll" 
%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe /codebase "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll"
%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe -u "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll"

@RD /S /Q "C:\RealtaScopeTech"

timeout 200