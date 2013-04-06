#!/bin/bash
g++ -g -Ilib -o queuetest.elf simqueue.cpp lib/*.cpp
if [ $? -eq 0 ]; then
    chmod +x queuetest.elf
    ./queuetest.elf
fi
echo
