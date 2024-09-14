#include <stdlib.h>
#include <stdio.h>

typedef unsigned char uc;

uc** create_array();
void free_array(uc ***m);

#define int_size 20


int main(void){
    
}


uc** create_array(){
  uc **m = (uc**) malloc(int_size*sizeof(uc*));

  for (int i=0; i<int_size; i++){
    m[i] = (uc*) malloc(int_size*sizeof(uc));
  }

  return (m);
}

void liberar_matriz(uc ***m){
   for (int i=0; i<int_size; i++){
        free((*m)[i]);
  }
  free(*m);
  *m = NULL; 
}