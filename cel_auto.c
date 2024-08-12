#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define tam 20
#define r 1
#define pop 200

int *check_n(int *a);
int avaliacao(int **popu, int *a);
void sexo(int ***popu, int **a);

int main(void){
    //Vetor com as celulas
    int *a = calloc((tam+2*r),sizeof(int));

    srand(time(0));

    //Colocando os valores no vetor, ja considerando o buffer
    for(int i=r; i<tam+r; i++){
        a[i] = rand() % 2;
        //printf("%d ", a[i]);
    }
    //printf("\n");

    //Inicializando a população de regras inicial
    int **popu = malloc(pop*sizeof(int*));
    for(int i=0; i<pop; i++){
        popu[i] = malloc(8*sizeof(int));
        for(int k=0; k<8; k++){
            popu[i][k] = rand() % 2;
        }
    }


    for(int i=0; i<60; i++){
        sexo(&popu, &a);
        //printf("----------------------\n");
    }

    int *p = check_n(a);
    for(int i=0; i<8; i++){
        printf("%d ", popu[avaliacao(popu, a)][i]);
    }
    printf("\n-----------------\n");
    for(int i=r; i<tam+r; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    for(int i=0; i<tam; i++){
        printf("%d ", popu[avaliacao(popu, a)][p[i]]);
    }
    printf("\n");





    free(a);
    for(int i=0; i<pop; i++){
        free(popu[i]);
    }
    free(popu);
    free(p);
    return 0;
}

int *check_n(int *a){
    int *p = malloc(tam*sizeof(int));

    int cont = 0;

    for(int i=r; i<tam+r; i++){
        if(a[i-1]==0 && a[i]==0 && a[i+1]==0){
            p[cont] = 0;
        }
        if(a[i-1]==0 && a[i]==0 && a[i+1]==1){
            p[cont] = 1;
        }
        if(a[i-1]==0 && a[i]==1 && a[i+1]==0){
            p[cont] = 2;
        }
        if(a[i-1]==0 && a[i]==1 && a[i+1]==1){
            p[cont] = 3;
        }
        if(a[i-1]==1 && a[i]==0 && a[i+1]==0){
            p[cont] = 4;
        }
        if(a[i-1]==1 && a[i]==0 && a[i+1]==1){
            p[cont] = 5;
        }
        if(a[i-1]==1 && a[i]==1 && a[i+1]==0){
            p[cont] = 6;
        }
        if(a[i-1]==1 && a[i]==1 && a[i+1]==1){
            p[cont] = 7;
        }


        cont++;
    }

    return p;
}

int avaliacao(int **popu, int *a){
    //Copiando a sequencia original
    int *cp = malloc(tam*sizeof(int));

    //Decidindo quem é o melhor
    int poggers = 0;
    int pnt_p = 0;

    int *p = check_n(a);

    for(int i=0; i<pop; i++){
        int pnts = 0;
        //Restaurando a lista original
        for(int j=0; j<tam; j++){
            cp[j] = a[j+r];
        }
        //Aplicando as regras do candidato
       for(int j=0; j<tam; j++){
            cp[j] = popu[i][p[j]];
            //printf("%d ", cp[j]);
            //Metodo de avaliação
            if(cp[j] == 0){
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

void sexo(int ***popu, int **a){
    int poggers = avaliacao(*popu, *a);
    //printf("%d\n", poggers);

    for(int i=0; i<pop; i++){
        /*for(int j=0; j<8; j++){
            printf("%d ", (*popu)[i][j]);
        }
        printf("\n");*/

        if(i != poggers){
            for(int j=0; j<4; j++){
                int n = rand()%8;
                (*popu)[i][n] = (*popu)[poggers][n];
            }
            // Introduce random mutations
            for(int j=0; j<2; j++){ // 2 random mutations
                int n = rand() % 8;
                (*popu)[i][n] = rand() % 2; // Randomly set to 0 or 1
            }
        }
    }
    //printf("---------------\n");
}