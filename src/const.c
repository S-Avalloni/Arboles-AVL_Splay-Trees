#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// #include "../include/avl.h"
// #include "../include/splay.h"

int main() {

  char title[20];
  
  srand(time(NULL));

  unsigned int *block = malloc(sizeof(int)*1024); // para escribir de a 4096 bytes

  for (int i = 10; i<= 14; i++) {
    int k = 0;
    snprintf(title, 19, "./data/dataset_%d", i);
    printf("Escribiendo archivo %s\n", title);
    FILE *archivo = fopen(title, "w+");

    if (archivo == NULL) {
      perror("algo pasó\n");
      return 1;
    }
    int max = 1<<i;
    int cont = 0;
    
    for (int j = 0; j<max; j++) {

      block[cont] = (unsigned int)((unsigned int)rand()<<1) | (rand()&1);
      ++cont;
      if (cont == 1024) {
        k++;
        fwrite(block, sizeof(int), cont, archivo);
        cont = 0;
      }
    }
    
    // No es necesario escribir de nuevo porque todos son mayores que
    // 2 a la 10
    fclose(archivo);
    printf("%d bloques escritos\n", k, cont);

  }

  free(block);
  block = NULL;

  return 0;
}