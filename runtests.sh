#!/bin/bash

TESTDIR=tests
BIN=./graph

echo "Compiling..."
make

for i in "$TESTDIR"/*.in
do
		TEST=${i%.in}
		echo "Running tests on $i"
		"$BIN" < "$i" | diff - "$TEST.out" | colordiff
done
