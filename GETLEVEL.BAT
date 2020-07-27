@echo off
if "%1" == "" goto usage
pc2sega /a0x1f0000 /um /f /r %1
pc2sega /a0x1f0000 /r resetlvl.bin
goto exit
:usage
Echo Must use filename to save example home1.lev
:exit

