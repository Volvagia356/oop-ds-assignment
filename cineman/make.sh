#!/bin/bash
g++ -g -Icineman -o cineman-debug.elf cineman.cpp cineman/*.cpp
if [ $? -eq 0 ]; then
    chmod +x cineman-debug.elf
    ./cineman-debug.elf
fi
echo
