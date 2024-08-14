maj:
	gcc maj.c -lm -o alg ; ./alg

val:
	gcc maj.c -lm -g -o alg ; valgrind ./alg

cel:
	gcc cel_auto.c -o alg ; ./alg