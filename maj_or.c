#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define tam 149
#define r 3
#define pop 500
#define m 150
#define gen 100

int *check_n(int *a);
int avaliacao(int **popu, int *a, int maj);
void sexo(int ***popu, int **a, int maj);

int main(void){
    int rules = pow(2, (2*r)+1);
    int n1 = 0;
    int n0 = 0;
    //Vetor com as celulas
    int *a = calloc((tam+2*r),sizeof(int));

    srand(time(0));

    //Colocando os valores no vetor, ja considerando o buffer
    for(int i=r; i<tam+r; i++){
        a[i] = rand() % 2;
        //printf("%d ", a[i]);
        if(a[i]==0){n0++;} else{n1++;}
    }

    int maj = 0;
    if(n1>n0){
        maj = 1;
    } else{
        maj = 0;
    }
    //printf("\n");

    //Inicializando a população de regras inicial
    int **popu = malloc(pop*sizeof(int*));
    for(int i=0; i<pop; i++){
        popu[i] = malloc(rules*sizeof(int));
        for(int k=0; k<rules; k++){
            popu[i][k] = rand() % 2;
        }
    }

    for(int i=0; i<gen; i++){
        sexo(&popu, &a, maj);
        //printf("----------------------\n");
    }

    printf("-------------Maj: %d-------------\n", maj);

    int *p = NULL;
    int *cp = calloc(tam+2*r, sizeof(int));
    for(int j=r; j<tam+r; j++){
        cp[j] = a[j];
    }
    int poggers = avaliacao(popu, a, maj);
    for(int j=0; j<m; j++){
        p = check_n(cp);
        for(int k=0; k<tam; k++){
            cp[k+r] = popu[poggers][p[k]];
            printf("%d", cp[k+r]);
        }
        printf("\n");
    }



    free(a);
    for(int i=0; i<pop; i++){
        free(popu[i]);
    }
    free(popu);
    free(p);
    free(cp);
    return 0;
}

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

int avaliacao(int **popu, int *a, int maj){
    //Copiando a sequencia original
    int *cp = calloc(tam+2*r, sizeof(int));

    //Decidindo quem é o melhor
    int poggers = 0;
    int pnt_p = 0;

    int *p = NULL;

    for(int i=0; i<pop; i++){
        int pnts = 0;
        //Restaurando a lista original
        for(int j=r; j<tam+r; j++){
            cp[j] = a[j];
        }
        //Aplicando as regras do candidato M vezes
        for(int j=0; j<m; j++){
            p = check_n(cp);
            for(int k=0; k<tam; k++){
                cp[k+r] = popu[i][p[k]];
            }
        }
        for(int j=0; j<tam; j++){
            if(cp[j] == maj){
                pnts++;
            }
        }
        //printf("\n");

        if(pnts > pnt_p){
            pnt_p = pnts;
            poggers = i;
        }
    }

    //printf("%d -> ", pnt_p);

    
    free(p);
    free(cp);
    return poggers;
}

void sexo(int ***popu, int **a, int maj){
    int rules = pow(2, (2*r)+1);
    int poggers = avaliacao(*popu, *a, maj);
    //printf("%d\n", poggers);

    for(int i=0; i<pop; i++){
        /*for(int j=0; j<rules; j++){
            printf("%d ", (*popu)[i][j]);
        }
        printf("\n");*/

        if(i != poggers){
            for(int j=0; j<(rules/4); j++){
                int n = rand()%rules;
                (*popu)[i][n] = (*popu)[poggers][n];
            }
            // Introduce random mutations
            for(int j=0; j<(rules/32); j++){
                int n = rand() % rules;
                (*popu)[i][n] = rand() % 2;
            }
        }
    }
    //printf("---------------\n");
}