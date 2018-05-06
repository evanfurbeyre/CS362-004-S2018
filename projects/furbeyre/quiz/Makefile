CFLAGS = -Wall -fpic -coverage -lm

testme:
	gcc testme.c -o testme $(CFLAGS)
	./testme

make clean:
	rm testme *.gcov *.gcda *.gcno
