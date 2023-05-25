build:
	gcc -Wall main.c -o main

sudoku: main
	./main

run-sudoku: main
	./test.sh

valgrind: run-sudoku
	valgrind --leak-check=full ./main

clean: 
	rm -rf main test.in test.out timer test_times tests/out
