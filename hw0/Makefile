.PHONY: clean

test: hw0.h hw0.c test_hw0_phase1.c
	clang -Wall -o run_hw0_tests hw0.c test_hw0_phase1.c -lcriterion -lm

clean:
	rm -rf run_hw0_tests

