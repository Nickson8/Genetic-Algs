maj:
	gcc maj.c -o alg -lm; ./alg

val:
	gcc maj.c -g -o alg -lm; valgrind ./alg

cel:
	gcc cel_auto.c -o alg ; ./alg

maj_or:
	gcc maj_or.c -o alg -lm; ./alg

point:
	gcc point.c -o alg; ./alg