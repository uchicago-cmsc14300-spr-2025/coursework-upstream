.PHONY: clean

seq: lab8.h lab8.c grayseq.c
	clang -Wall -o grayseq lab8.c grayseq.c -pthread

par: lab8.h lab8.c graypar.c
	clang -Wall -o graypar lab8.c graypar.c -pthread

clean:
	rm -rf a.out grayseq graypar

