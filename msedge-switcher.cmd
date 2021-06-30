@echo off
title Patch MS Edge
:check_Permissions
net session >nul 2>&1
if %errorLevel% == 0 (
    goto start
) else (
    echo Error! Right Click on the file and then choose 'Run As Administrator' & pause >nul & exit
)

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
