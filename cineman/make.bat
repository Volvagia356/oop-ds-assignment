@ECHO OFF
TITLE Cineman Test
CHCP 437
g++ -Icineman -o cineman.exe cineman.cpp cineman/*.cpp
IF %ERRORLEVEL% EQU 0 (cineman.exe) ELSE PAUSE