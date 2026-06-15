#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/trees.h"

#define c 5

#define N 0b10000000000000000000000000

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

int dataset() {
  
  srand(time(NULL));

  unsigned int *block = malloc(sizeof(int)*1024); // para escribir de a 4096 bytes
  char title[] = "./data/dataset_25";
  FILE *archivo = fopen(title, "w+");
  
  if (archivo == NULL) {
    perror("algo pasó\n");
    return 1;
  }
  
  int k = 0;
  int cont = 0;
  
  printf("Escribiendo archivo %s\n", title);
  
  for (int j = 0; j<N; j++) {

    block[cont] = (unsigned int)((unsigned int)rand()<<1) | (rand()&1);
    ++cont;
    if (cont == 1024) {
      k++;
      fwrite(block, sizeof(int), cont, archivo);
      cont = 0;
    }
  }
  
  fclose(archivo);
  printf("%d bloques escritos\n", k);


  free(block);
  block = NULL;

  return 0;
}

int main() {
  return dataset();
}