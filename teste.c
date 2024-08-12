#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam 10
#define r 3

int *check_n(int *a){
    int *p = malloc(tam * sizeof(int));
    int cont = 0;

    for(int i = r; i < tam + r; i++){
        int bit_value = 0;

        // Constructing the 7-bit value
        bit_value |= (a[i-3] << 6);
        bit_value |= (a[i-2] << 5);
        bit_value |= (a[i-1] << 4);
        bit_value |= (a[i] << 3);
        bit_value |= (a[i+1] << 2);
        bit_value |= (a[i+2] << 1);
        bit_value |= (a[i+3]);

        // Store the 7-bit value in the p array
        p[cont] = bit_value;
        cont++;
    }

    return p;
}

int main(void){
    //Vetor com as celulas
    int *a = calloc((tam+2*r),sizeof(int));

    srand(time(0));

    //Colocando os valores no vetor, ja considerando o buffer
    for(int i=r; i<tam+r; i++){
        a[i] = rand() % 2;
        printf("%d ", a[i]);
    }
    printf("\n");

    int *p = check_n(a);

    for(int i=0; i<tam; i++){
        printf("%d ", p[i]);
    }
}