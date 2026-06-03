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

int zag(Avl* arbol) {
  Avl* nueva_raiz = arbol->B;
  if (nueva_raiz == NULL) {
    perror("Lado derecho del arbol no puede ser nulo");
    return 0;
  }
  arbol->B = (nueva_raiz)->A;
  nueva_raiz->A = arbol;
  
  // Debemos recalcular altura de abajo hacia arriba
  arbol->altura = 1 + max(altura(arbol->A), altura(arbol->B));
  nueva_raiz->altura = 1 + max(altura(nueva_raiz->A),altura(nueva_raiz->B));

  arbol = nueva_raiz;
  return 1;
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
}

int insert(Avl* arbol, int x) {
  if (arbol == NULL) {
    
    arbol = malloc(sizeof(Avl));
    if (arbol == NULL) return 1;

    arbol->r = x;
    arbol->A = NULL;
    arbol->B = NULL;
    arbol->altura = 1;
    return 1;
  } else if (arbol -> r > x) {
    insert(arbol->A, x);
  } else if (arbol -> r < x){
    insert(arbol -> B, x);
  } else {
    perror("No se pueden insertar un elemento repetido");
    return 0;
  }


  int bf_root = balance_factor(arbol);
  int bf_A    = balance_factor(arbol->A);
  int bf_B    = balance_factor(arbol->B);

  if (bf_root == 2 && bf_A >= 0) {      // LL
    if (zig(arbol) == 0) {
      perror("arbol raiz nulo en operacion LL");
      return 0;
    }
  } else if (bf_root == -2 && bf_B <= 0) { // RR
    if (zag(arbol) == 0) {
      perror("arbol raiz nulo en operacion RR");
      return 0;
    }
  } else if (bf_root == 2 && bf_A < 0) {  // LR
    if (zag(arbol->A) == 0) {
      perror("arbol izquierdo nulo en operacion LR");
      return 0;
    }

    if (zig(arbol) == 0) {
      perror("arbol raiz nulo en operacion LR");
      return 0;
    }
  } else if (bf_root == -2 && bf_B > 0) { // RL
    if (zag(arbol->B) == 0) {
      perror("arbol derecho nulo en operacion LR");
      return 0;
    }

    if (zig(arbol) == 0) {
      perror("arbol raiz nulo en operacion LR");
      return 0;
    }
  } else {
    arbol->altura = 1 + max(altura(arbol->A), altura(arbol->B));
  }

  return 0;
}