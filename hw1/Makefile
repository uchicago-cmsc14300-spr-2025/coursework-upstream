.PHONY: clean

test1: hw1.h hw1.c test_hw1_phase1.c
	clang -Wall -o run_hw1_tests hw1.c test_hw1_phase1.c -lcriterion -lm

clean:
	rm -rf a.out run_hw1_tests
