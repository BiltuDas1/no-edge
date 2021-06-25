@echo off
title Patch MS Edge
set edge=%programdata%\MSEDGE
if not exist "%edge%" echo %edge% Doesn't exist! & goto exit
ren "%edge%\msedge.exe" "msedge.exe_bak"
for %%a in (%0) do set path=%%~dpa
set path=.%path%
set path=%path:~1,-1%
move "%path%\msedge.exe" "%edge%"
cls
if exist "%edge%\msedge.exe" echo Operation Successful!
if not exist "%edge%\msedge.exe" echo Operation Failed!
:exit
pause>nul
exit
