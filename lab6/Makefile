# Makefile for Lab 6, CMSC 14300, Spring 2025

# run 'make all' or just 'make' to compile both targets
# run 'make clean' to clean up

all : tsr tsi

# tsr stands for "tree sum, recursive"
tsr : tree.h tree.c tree_sum_recursive.c
	clang -g -o tsr tree.c tree_sum_recursive.c

# tsi stands for "tree sum, iterative"
tsi : tree.h tree.c tree_list.h tree_list.c tree_stack.h tree_stack.c tree_sum_iterative.c
	clang -g -o tsi tree.c tree_list.c tree_stack.c tree_sum_iterative.c

# run 'make clean' to remove generated files
clean :
	rm -rf *.dSYM tsi tsr
