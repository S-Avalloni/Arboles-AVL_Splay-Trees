#include <stdlib.h>
#include "avl.h"


int altura(Avl* arbol) {
  if (arbol == NULL) {
    return 0;
  }

  return arbol->altura;
}

int balance_factor(Avl* arbol) {
  if (arbol == NULL) {
    return 0;
  }

  return altura(arbol->A) - altura(arbol->B);

}

Avl* zig(Avl* arbol) {
  Avl* nueva_raiz = arbol->A;
  if (nueva_raiz == NULL) {
    perror("Lado izquierdo del arbol no puede ser nulo");
    return NULL;
  }
  arbol->A = (nueva_raiz)->B;
  nueva_raiz->B = arbol;
  
  // Debemos recalcular altura de abajo hacia arriba
  arbol->altura = 1 + max(altura(arbol->A), altura(arbol->B));
  nueva_raiz->altura = 1 + max(altura(nueva_raiz->A),altura(nueva_raiz->B));

  return nueva_raiz;
}

Avl* zag(Avl* arbol) {
  Avl* nueva_raiz = arbol->B;
  if (nueva_raiz == NULL) {
    perror("Lado derecho del arbol no puede ser nulo");
    return NULL;
  }
  arbol->B = (nueva_raiz)->A;
  nueva_raiz->A = arbol;
  
  // Debemos recalcular altura de abajo hacia arriba
  arbol->altura = 1 + max(altura(arbol->A), altura(arbol->B));
  nueva_raiz->altura = 1 + max(altura(nueva_raiz->A),altura(nueva_raiz->B));

  return nueva_raiz;
}

Avl* search(Avl* arbol, int x) {
  Avl* current = arbol;

  for(;;) {

    if (current==NULL || current->r == x) {
      return current;
    } else if (current -> r > x) {
      current = current -> A;
    } else {
      current = current -> B;
    }
  }

  return current;
}

Avl* insert(Avl* arbol, int x) {
  if (arbol == NULL) {
    
    arbol = malloc(sizeof(Avl));

    arbol->r = x;
    arbol->A = NULL;
    arbol->B = NULL;
    arbol->altura = 1;
    return arbol;
  } else if (arbol -> r > x) {
    arbol->A = insert(arbol->A, x);
  } else if (arbol -> r < x){
    arbol->B = insert(arbol -> B, x);
  } else {
    perror("No se pueden insertar un elemento repetido");
    return arbol;
  }


  int bf_root = balance_factor(arbol);
  int bf_A    = balance_factor(arbol->A);
  int bf_B    = balance_factor(arbol->B);

  if (bf_root == 2 && bf_A >= 0) {      // LL
    arbol = zig(arbol);
  } else if (bf_root == -2 && bf_B <= 0) { // RR
    arbol = zag(arbol);
  } else if (bf_root == 2 && bf_A < 0) {  // LR
    arbol->A = zag(arbol->A);
    arbol = zig(arbol);
  } else if (bf_root == -2 && bf_B > 0) { // RL
    arbol->B = zag(arbol->B);
    arbol = zig(arbol);
  } else {
    arbol->altura = 1 + max(altura(arbol->A), altura(arbol->B));
  }

  if (arbol == NULL) {
    perror("Hubo un error y no se insertó bien el elemento");
  }
  return arbol;
}