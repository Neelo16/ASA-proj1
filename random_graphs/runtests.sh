#!/bin/bash

FILE=../graph.c

echo "Compiling..."
gcc -o graph -O3 -ansi -Wall $FILE -lm

for i in *.in
do
		TEST=${i%.in}
		echo "Running tests on $i"
		{ time ./graph < "$i" ; } 2> "$TEST.time"
done
