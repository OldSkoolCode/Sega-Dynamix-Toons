@echo off
if "%1" == "" goto :usage
pc2sega -g -a0x20000 %1 >nul
pc2sega /v viewspr.bin >nul
goto :exit
:usage
@echo ----- Usage viewanm [filename.ext]
:exit

