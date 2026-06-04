#include <stdlib.h>
#include <stdio.h>
// #include "../include/avl.h"
#include "../include/splay.h"


int main() {
  SplayTree* cabeza = NULL;
  cabeza = insert(cabeza, 1);
  cabeza = insert(cabeza, 4);
  cabeza = insert(cabeza, 5);
  cabeza = insert(cabeza, 3);
  cabeza = insert(cabeza, 2);
  cabeza = insert(cabeza, 7);

  printf("%d\n", cabeza->r);

  delete(cabeza);
  return 0;
}