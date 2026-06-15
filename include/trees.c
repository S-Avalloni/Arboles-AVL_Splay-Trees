#include <stdlib.h>
#include "trees.h"

int compare_asc(const void *a, const void *b) {
    unsigned int val_a = *(const unsigned int *)a;
    unsigned int val_b = *(const unsigned int *)b;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

int geom(unsigned int N) {
  unsigned int conteo;
  do {
    conteo = 0;
    // bernoulli(1/32) hasta que haya un acierto
    while ((rand()&0b11111) != 0b11111) {
      conteo++;
    }
    
  } while (conteo>=N); // Se resamplea si es que se pasa de N

  return conteo;

}

int unif(unsigned int N) {
  unsigned int resultado;

  unsigned int mask = N - 1;
  mask |= mask >> 1;
  mask |= mask >> 2;
  mask |= mask >> 4;
  mask |= mask >> 8;
  mask |= mask >> 16;

  do {
    resultado =   rand()&mask;
  } while (resultado>=N);
  return resultado;
}

int seq(unsigned int N) {
  return N;
}

void to_array(Avl *arbol, unsigned int *lista, int *idx) {
  if (arbol->A != NULL) {
    to_array(arbol->A, lista, idx);
  }
  lista[*idx] = arbol->r;
  *idx += 1;
  if (arbol->B != NULL) {
    to_array(arbol->B, lista, idx);
  }
}