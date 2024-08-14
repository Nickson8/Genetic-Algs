#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define tam 149
#define r 3
#define pop 1000
#define m 149

int *check_n(int *a);
int avaliacao(int **popu);
void sexo(int ***popu);
int teste(int *poggers);

int main(void){
    //Número de regras da relevância table
    int rules = pow(2, (2*r)+1);

    srand(time(0));

    //Inicializando a população de regras inicias aleatorias
    int **popu = malloc(pop*sizeof(int*));
    for(int i=0; i<pop; i++){
        popu[i] = malloc(rules*sizeof(int));
        for(int k=0; k<rules; k++){
            popu[i][k] = rand() % 2;
        }
    }

    //Loop para as gerações
    for(int i=0; i<40; i++){
        sexo(&popu);
        printf("%d ", i);
        fflush(stdout);
        //printf("----------------------\n");
    }
    printf("\n");

    int *poggers = popu[avaliacao(popu)];

    double cont=0;
    int vezes = 100;
    for(int i=0; i<vezes; i++){
        cont += teste(poggers);
    }
    printf("\n---%.2f---\n", (cont/vezes));


    for(int i=0; i<pop; i++){
        free(popu[i]);
    }
    free(popu);
    //free(p);
    //free(cp);
    return 0;
}

//Função para calcular a posição relativa de uma célula, retorna um Vetor com as posições de cada célula
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

//Função para avaliar a população, retorna o indivíduo com mais fitness
int avaliacao(int **popu){
    //Var para contar 0s e 1s
    int n1, n0;
    //Vetor com as celulas
    int *a = calloc((tam+2*r),sizeof(int));

    //Decidindo quem é o melhor
    int poggers = 0;
    int pnt_p = 0;

    int *p = NULL;

    int pnts, maj;

    for(int i=0; i<pop; i++){
        //Testando o individuo para varias CI aleatorias
        pnts = 0;
        for(int l=0; l<10; l++){
            maj = 0;
            n1 = 0;
            n0 =0;
            //Colocando os valores no vetor, ja considerando o buffer
            for(int j=r; j<tam+r; j++){
                a[j] = rand() % 2;
                //printf("%d ", a[j]);
                if(a[j]==0){n0++;} else{n1++;}
            }
            
            //Verificando qual é a maioria
            if(n1>n0){
                maj = 1;
            } else{
                maj = 0;
            }
            //Aplicando as regras do candidato M vezes
            for(int j=0; j<m; j++){
                if(p!=NULL){
                    free(p);
                }
                p = check_n(a);
                for(int k=0; k<tam; k++){
                    a[k+r] = popu[i][p[k]];
                }
            }
            //Método de avaliação
            for(int j=0; j<tam; j++){
                if(a[j] == maj){
                    pnts++;
                }
            }
        }

        if(pnts > pnt_p){
            pnt_p = pnts;
            poggers = i;
        }
    }

    //printf("%d -> ", pnt_p);

    
    free(p);
    free(a);
    return poggers;
}

//Função para cruzar a população com o poggers
void sexo(int ***popu){
    int rules = pow(2, (2*r)+1);
    int poggers = avaliacao(*popu);
    //printf("%d\n", poggers);

    for(int i=0; i<pop; i++){
        /*for(int j=0; j<rules; j++){
            printf("%d ", (*popu)[i][j]);
        }
        printf("\n");*/

        if(i != poggers){
            //Cruzando com o poggers
            for(int j=0; j<(rules/2); j++){
                int n = rand()%rules;
                (*popu)[i][n] = (*popu)[poggers][n];
            }
            // Introduce random mutations
            for(int j=0; j<(rules/16); j++){
                int n = rand() % rules;
                (*popu)[i][n] = rand() % 2;
            }
        }
    }
    //printf("---------------\n");
}

int teste(int *poggers){
    //Número de regras da relevância table
    int rules = pow(2, (2*r)+1);

    //Var para contar 0s e 1s
    int n1 = 0;
    int n0 = 0;
    //Vetor com as celulas
    int *a = calloc((tam+2*r),sizeof(int));

    //Colocando os valores no vetor, ja considerando o buffer
    for(int i=r; i<tam+r; i++){
        a[i] = rand() % 2;
        //printf("%d ", a[i]);
        if(a[i]==0){n0++;} else{n1++;}
    }
    
    //Verificando qual é a maioria
    int maj = 0;
    if(n1>n0){
        maj = 1;
    } else{
        maj = 0;
    }

    /***RESULTADOS FINAIS***/
    printf("-------------Maj: %d-------------\n", maj);
    
    //Vetor das posições da configuração inicial
    int *p = NULL;
    //Aplicando a rule table do poggers na CI M vezes e printando o resultado 
    for(int j=0; j<m; j++){
        if(p!=NULL){
            free(p);
        }
        p = check_n(a);
        for(int k=0; k<tam; k++){
            a[k+r] = poggers[p[k]];
            if(j<18 || j>130){printf("%d", a[k+r]);}
        }
        if(j<18 || j>130){printf("\n");}
        if(j==40 || j==41 || j==42){printf("             .\n");}
    }

    int cont=0;
    for(int i=r; i<tam+r; i++){
        if(a[i] == maj){
            cont++;
        }
    }
    
    
    if(cont==149){
        return 1;
    }

    return 0;

    free(a);
    free(p);
}