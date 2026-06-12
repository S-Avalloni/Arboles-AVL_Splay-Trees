#include <stdlib.h>
#include <stdio.h>
#include "../include/trees.h"




int main() {

  Avl* cabeza = NULL;
  cabeza = insert(cabeza, 1);
  cabeza = insert(cabeza, 4);
  cabeza = insert(cabeza, 5);
  cabeza = insert(cabeza, 3);
  cabeza = insert(cabeza, 2);
  cabeza = insert(cabeza, 7);
  void *resultado = search(cabeza, 5);

  printf("cabeza: %p\nresultado: %p\n", cabeza, resultado);

  delete(cabeza);
  cabeza = NULL;
  return 0;
}

