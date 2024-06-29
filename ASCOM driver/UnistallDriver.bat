%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe -u "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll" runhidden 32bit
%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe /codebase "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll" runhidden 64bit
%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\regasm.exe -u "C:\RealtaScopeTech\ASCOM.EBB.Focuser.dll" runhidden 64bit

@RD /S /Q "C:\RealtaScopeTech"

timeout 200