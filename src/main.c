#include <stdlib.h>
#include <stdio.h>
#include "../include/avl.h"
// #include "../include/splay.h"

void preorder(Avl* arbol) {
  if (arbol->A != NULL) {
    preorder(arbol->A);
  }
  printf("%d\n", arbol->r);

  if (arbol->B != NULL) {
    preorder(arbol->B);
  } 

}


int main() {
  printf("%d\n%u\n", 1928130327, (unsigned int)1928130327<<1);
  // printf("%u\n", (unsigned int)RAND_MAX);
  // printf("%u\n", (unsigned int)RAND_MAX<<1);
  // printf("%u\n", (unsigned int)RAND_MAX<<2);
  Avl* cabeza = NULL;
  cabeza = insert_avl(cabeza, 1);
  cabeza = insert_avl(cabeza, 4);
  cabeza = insert_avl(cabeza, 5);
  cabeza = insert_avl(cabeza, 3);
  cabeza = insert_avl(cabeza, 2);
  cabeza = insert_avl(cabeza, 7);

  printf("%d\n", cabeza->r);

  Avl* ptro = search_avl(cabeza, 5);

  printf("%d\n\n", ptro->r);

  preorder(cabeza);

  delete_avl(cabeza);
  ptro = NULL;
  cabeza = NULL;
  return 0;
}

