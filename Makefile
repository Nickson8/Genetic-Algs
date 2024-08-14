maj:
	gcc maj.c -o alg ; ./alg

val:
	gcc maj.c -g -o alg ; valgrind ./alg

cel:
	gcc cel_auto.c -o alg ; ./alg