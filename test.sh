#!/bin/bash

test_sudoku() {
    nr_tests=7
    src_name=(main.c)
    tests=( $(seq 1 $(($nr_tests))) )
    run_tests 1
}

run_tests() {
    rm -rf tests/out/
	mkdir -p tests/out/

	rm test_times
	touch test_times

    for i in "${tests[@]}"; do
		IN=tests/in/test$i.in
		REF=tests/ref/test$i.ref
		OUT=tests/out/test$i.out

		cp $IN test.in

		touch test.out
		chmod 666 test.out

		make sudoku
		(time make sudoku) &> timer
		t=`cat timer | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1`
		echo "time test$i = $t s" >> test_times

		cp test.out $OUT

	done
}

test_sudoku
