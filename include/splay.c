#include <stdlib.h>
#include "splay.h"


SplayTree* zig(SplayTree* arbol) {
  SplayTree* nueva_raiz = arbol->A;
  if (nueva_raiz == NULL) {
    perror("Lado izquierdo del arbol no puede ser nulo");
    return NULL;
  }
  arbol->A = (nueva_raiz)->B;
  nueva_raiz->B = arbol;
  
  return nueva_raiz;
}

SplayTree* zag(SplayTree* arbol) {
  SplayTree* nueva_raiz = arbol->B;
  if (nueva_raiz == NULL) {
    perror("Lado derecho del arbol no puede ser nulo");
    return NULL;
  }
  arbol->B = (nueva_raiz)->A;
  nueva_raiz->A = arbol;

  return nueva_raiz;
}

SplayTree* zigzig(SplayTree* arbol) {
  return zig(zig(arbol));
}

SplayTree* zagzag(SplayTree* arbol) {
  return zag(zag(arbol));
}

SplayTree* zigzag(SplayTree* arbol) {
  arbol->A = zag(arbol->A);
  return zig(arbol);
}

SplayTree* zagzig(SplayTree* arbol) {
  arbol->B = zig(arbol->B);
  return zag(arbol);
}

SplayTree* splay(SplayTree* arbol, int x) {

  if (arbol == NULL || arbol->r == x)
    return arbol;

  if (arbol->r > x) {
    if (arbol->A == NULL) {
      return arbol;
    }
    if (arbol->A->r > x) {
      arbol->A->A = splay(arbol->A->A, x);
      arbol = zig(arbol);
    } else if (arbol->A->r < x) {
      arbol->A->B = splay(arbol->A->B, x);
      if (arbol->A->B != NULL)
        arbol->A = zag(arbol->A);
    }

    return (arbol->A == NULL) ? arbol : zig(arbol);

  } else {
    if (arbol->B == NULL) {
      return arbol;
    }
    
    if (arbol->B->r > x) {
      arbol->B->A = splay(arbol->B->A, x);
      if (arbol->B->A != NULL) {
        arbol->B = zig(arbol->B);
      }
    } else if (arbol->B->r < x) {
      arbol->B->B = splay(arbol->B->B, x);
      arbol = zag(arbol);
    }

    return (arbol->B == NULL) ? arbol : zag(arbol);

  }

}