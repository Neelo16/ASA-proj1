#!/bin/bash

FILE=graph.c
TESTDIR=tests

echo "Compiling..."
make

for i in "$TESTDIR"/*.in
do
		TEST=${i%.in}
		echo "Running tests on $i"
		./graph < "$i" | diff - "$TEST.out" | colordiff
done
