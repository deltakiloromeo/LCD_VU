#!/bin/bash
find . -name "Arduino.h"
cp ${{ matrix.example-path }}.ino ${{ matrix.example-path }}.cpp
g++ ${{ matrix.ccov-options }} ${{ matrix.include-paths }} ${{ matrix.example-path }}.cpp -o program
./program