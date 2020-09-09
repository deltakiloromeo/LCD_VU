#!/bin/bash
cp $1.ino $1.cpp
g++ $2 $3 $1.cpp -o program
./program