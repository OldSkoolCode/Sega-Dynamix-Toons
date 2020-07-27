@echo off
if "%1" == "" goto usage
pc2sega /a0x1f0004 /r %1
goto exit
:usage
Echo Must use filename to save example home1.lev
:exit

