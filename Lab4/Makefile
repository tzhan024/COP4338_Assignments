all:	bitops

bitops:	bitops.o
	gcc bitops.o -o bitops

bitops.o:	bitops.c
	gcc -c bitops.c -o bitops.o

clean:
	rm -f bitops bitops.o core *~