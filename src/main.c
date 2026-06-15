#include <stdlib.h>
#include <stdio.h>
#include "../include/trees.h"

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"


int main() {

  Avl* cabeza = NULL;
  cabeza = insert(cabeza, 1);
  cabeza = insert(cabeza, 4);
  cabeza = insert(cabeza, 5);
  cabeza = insert(cabeza, 3);
  cabeza = insert(cabeza, 2);
  cabeza = insert(cabeza, 7);
  void *resultado = search(cabeza, 5);

  printf(BLUE("cabeza: %p") "\n" GREEN("resultado: %p") "\n", cabeza, resultado);

  delete(cabeza);
  cabeza = NULL;
  return 0;
}

