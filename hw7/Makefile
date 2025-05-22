.PHONY: clean

knightshift: knightshift.h knightshift.c knightshell.h knightshell.c computer-player.h computer-player.c
	clang -Wall -o knightshift knightshift.c knightshell.c computer-player.c

debug: knightshift.h knightshift.c knightshell.h knightshell.c computer-player.h computer-player.c
	clang -g -Wall -o knightshift knightshift.c knightshell.c computer-player.c

test: knightshift.h knightshift.c computer-player.h computer-player.c test_hw7_phase1.c
	clang -Wall -o run_hw7_tests knightshift.c computer-player.c test_hw7_phase1.c -lcriterion

clean:
	rm -rf knightshift run_hw7_tests *.dSYM

