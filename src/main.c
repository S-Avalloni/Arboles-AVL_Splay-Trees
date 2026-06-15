#include <stdlib.h>
#include <stdio.h>
#include "../include/trees.h"

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

void to_array(SplayTree *arbol, unsigned int *lista, int *idx) {
  if (arbol->A != NULL) {
    to_array(arbol->A, lista, idx);
  }
  lista[*idx] = arbol->r;
  *idx += 1;
  if (arbol->B != NULL) {
    to_array(arbol->B, lista, idx);
  }
}


int main() {

  SplayTreeContext *ctx = init_ctx_spl(10);
  unsigned int *test = malloc(sizeof(unsigned int)*10);
  int i = 0;

  SplayTree* cabeza = NULL;
  cabeza = insert(ctx, cabeza, 5);
  cabeza = insert(ctx, cabeza, 1);
  cabeza = insert(ctx, cabeza, 7);
  cabeza = insert(ctx, cabeza, 4);
  cabeza = insert(ctx, cabeza, 3);
  cabeza = insert(ctx, cabeza, 2);
  cabeza = search(cabeza, 5);

  to_array(cabeza, test, &i);

  for(int j = 0; j<i; j++) {
    printf("%u\n", test[j]);
  }

  delete(ctx);
  free(test);
  return 0;
}

