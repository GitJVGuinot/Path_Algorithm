@echo off
cls
echo Compilando archivos fuente...

cl /nologo /EHsc /std:c++17 ^
/I ..\includes ^
/Fe:..\bin\main.exe ..\source\*.cc

echo Compilacion finalizada.
