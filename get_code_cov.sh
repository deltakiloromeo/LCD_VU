#!/bin/bash
for filename in `find . | egrep '\.cpp'`; 
do 
  #gcov-5 -n -o . $filename > /dev/null;
  gcov-5 -w -o . $filename; 
done