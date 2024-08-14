#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define tam 149
#define r 3
#define pop 5000
#define m 80

int *check_n(int *a, int *p);
int avaliacao(int **popu, int rules, int *a, int *p);
void sexo(int ***popu, int rules, int *a, int *p);
int teste(int *poggers, int rules, int *a, int *p);

int main(void) {
    int rules = pow(2, (2*r)+1);

    srand(time(0));

    // Allocate population
    int **popu = malloc(pop * sizeof(int*));
    for (int i = 0; i < pop; i++) {
        popu[i] = malloc(rules * sizeof(int));
        for (int k = 0; k < rules; k++) {
            popu[i][k] = rand() % 2;
        }
    }

    int *a = calloc((tam+2*r), sizeof(int)); // Pre-allocated buffer
    int *p = malloc(tam * sizeof(int));      // Pre-allocated buffer

    // Loop for generations
    for (int i = 0; i < 30; i++) {
        sexo(&popu, rules, a, p);
        printf("%d ", i);
        fflush(stdout);
    }
    printf("\n");

    int *poggers = popu[avaliacao(popu, rules, a, p)];

    double cont = 0;
    int vezes = 100;
    for (int i = 0; i < vezes; i++) {
        cont += teste(poggers, rules, a, p);
    }
    printf("\n---%.2f---\n", (cont/vezes));

    // Free memory
    for (int i = 0; i < pop; i++) {
        free(popu[i]);
    }
    free(popu);
    free(a);
    free(p);
    return 0;
}

int *check_n(int *a, int *p) {
    int cont = 0;
    for (int i = r; i < tam + r; i++) {
        int bit_value = 0;
        bit_value |= (a[i-3] << 6);
        bit_value |= (a[i-2] << 5);
        bit_value |= (a[i-1] << 4);
        bit_value |= (a[i] << 3);
        bit_value |= (a[i+1] << 2);
        bit_value |= (a[i+2] << 1);
        bit_value |= (a[i+3]);

        p[cont] = bit_value;
        cont++;
    }
    return p;
}

int avaliacao(int **popu, int rules, int *a, int *p) {
    int n1, n0;
    int poggers = 0;
    int pnt_p = 0;

    int pnts, maj;

    for (int i = 0; i < pop; i++) {
        pnts = 0;
        for (int l = 0; l < 11; l++) {
            maj = 0;
            n1 = 0;
            n0 = 0;

            for (int j = r; j < tam + r; j++) {
                a[j] = rand() % 2;
                if (a[j] == 0) n0++; else n1++;
            }

            maj = (n1 > n0) ? 1 : 0;

            for (int j = 0; j < m; j++) {
                p = check_n(a, p);
                for (int k = 0; k < tam; k++) {
                    a[k+r] = popu[i][p[k]];
                }
            }

            for (int j = 0; j < tam; j++) {
                if (a[j] == maj) {
                    pnts++;
                }
            }
        }

        if (pnts > pnt_p) {
            pnt_p = pnts;
            poggers = i;
        }
    }

    return poggers;
}

void sexo(int ***popu, int rules, int *a, int *p) {
    int poggers = avaliacao(*popu, rules, a, p);

    for (int i = 0; i < pop; i++) {
        if (i != poggers) {
            for (int j = 0; j < (rules/2); j++) {
                int n = rand() % rules;
                (*popu)[i][n] = (*popu)[poggers][n];
            }
            for (int j = 0; j < (rules/16); j++) {
                int n = rand() % rules;
                (*popu)[i][n] = rand() % 2;
            }
        }
    }
}

int teste(int *poggers, int rules, int *a, int *p) {
    int n1 = 0;
    int n0 = 0;

    for (int i = r; i < tam + r; i++) {
        a[i] = rand() % 2;
        if (a[i] == 0) n0++; else n1++;
    }

    int maj = (n1 > n0) ? 1 : 0;

    printf("-------------Maj: %d-------------\n", maj);

    for (int j = 0; j < m; j++) {
        p = check_n(a, p);
        for (int k = 0; k < tam; k++) {
            a[k+r] = poggers[p[k]];
            if (j < 18 || j > m-18) printf("%d", a[k+r]);
        }
        if (j < 18 || j > m-18) printf("\n");
        if (j == 40 || j == 41 || j == 42) printf("             .\n");
    }

    int cont = 0;
    for (int i = r; i < tam + r; i++) {
        if (a[i] == maj) cont++;
    }

    return (cont > m-10) ? 1 : 0;
}