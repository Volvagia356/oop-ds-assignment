@ECHO OFF
TITLE SIMQueue Test
CHCP 437
g++ -Ilib -o simqueue.exe simqueue.cpp lib/*.cpp
IF %ERRORLEVEL% EQU 0 (
MODE CON: COLS=80 LINES=25
simqueue.exe
) ELSE PAUSE