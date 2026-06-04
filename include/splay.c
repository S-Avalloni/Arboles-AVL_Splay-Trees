#include <stdlib.h>
#include <stdio.h>
#include "splay.h"

SplayTree* izq(SplayTree* arbol) {
  if (arbol == NULL || arbol->A == NULL) {
    return NULL;
  }

  return arbol->A;
}

SplayTree* der(SplayTree* arbol) {
  if (arbol == NULL || arbol->B == NULL) {
    return NULL;
  }

  return arbol->B;
}

SplayTree* pad(SplayTree* arbol) {
  if (arbol == NULL || arbol->Padre == NULL) {
    return NULL;
  }

  return arbol->Padre;
}


SplayTree* zig(SplayTree* arbol) {
  if (izq(arbol) == NULL) {
    perror("No se puede hacer zig con nodo nulo o nodo izquierdo nulo\n");
    return arbol;
  }
  
  if (pad(arbol) != NULL) {
    if (pad(arbol)->A == arbol) {
      pad(arbol)->A = arbol->A;
    } else {
      pad(arbol)->B = arbol->A;
    }
  }

  SplayTree* temp;
  arbol->A->Padre = pad(arbol);
  if (der(arbol->A) != NULL) {
    arbol->A->B->Padre = arbol;
  }

  temp = arbol->A->B;
  arbol->A->B = arbol;
  arbol->Padre = arbol->A;
  arbol->A = temp;

  return arbol->Padre;
}

SplayTree* zag(SplayTree* arbol) {
  if (der(arbol) == NULL) {
    perror("No se puede hacer zag con nodo nulo o nodo derecho nulo\n");
    return arbol;
  }
  
  if (pad(arbol) != NULL) {
    if (pad(arbol)->A == arbol) {
      pad(arbol)->A = arbol->B;
    } else {
      pad(arbol)->B = arbol->B;
    }
  }

  SplayTree* temp;
  arbol->B->Padre = pad(arbol);
  if (izq(arbol->B) != NULL) {
    arbol->B->A->Padre = arbol;
  }

  temp = arbol->B->A;
  arbol->B->A = arbol;
  arbol->Padre = arbol->B;
  arbol->B = temp;

  return arbol->Padre;

}

SplayTree* zigzig(SplayTree* arbol) {
  return zig(zig(arbol));
}

SplayTree* zagzag(SplayTree* arbol) {
  return zag(zag(arbol));
}

SplayTree* zigzag(SplayTree* arbol) {
  zag(arbol->A);
  return zig(arbol);
}

SplayTree* zagzig(SplayTree* arbol) {
  zig(arbol->B);
  return zag(arbol);
}

SplayTree* splay(SplayTree* arbol) {

  // Asumimos que estamos en el arbol que queremos
  // llevar hasta la raiz

  while (pad(pad(arbol))!=NULL) {

    if (arbol->r < pad(pad(arbol))->r) { // a la izquierda del abuelo
      if (arbol->r < pad(arbol)->r) { // a la izquierda de su padre
        // arbol->A->A == arbol;
        zigzig(pad(pad(arbol)));
      } else {
        zigzag(pad(pad(arbol)));
      }
    } else {
      if (arbol->r < pad(arbol)->r) {
        zagzig(pad(pad(arbol)));
      } else {
        zagzag(pad(pad(arbol)));
      }
    }
  }

  if (pad(arbol) == NULL) {
    return arbol;
  }
  if (pad(arbol->Padre) == NULL) {
    if (pad(arbol)->A == arbol) {
      return zig(arbol->Padre);
    } else {
      return zag(arbol->Padre);
    }
  }

  return arbol;
}

SplayTree* search(SplayTree* arbol, int x) {
  
  if (arbol == NULL) {
    perror("Busqueda en un arbol vacío\n");
    return arbol;
  }
  SplayTree* current = arbol;

  for (;;) {

    if (x < current->r) {
      if (current->A == NULL) {
        break;
      }
      current = current->A;
    } else {
      if (current->B == NULL) {
        break;
      }
      current = current->B;
    }
  }

  return splay(current);
}

SplayTree* insert(SplayTree* arbol, int x) {
  
  SplayTree* current;

  if (arbol == NULL) {
    current = malloc(sizeof(SplayTree));
    current->r = x;
    current->A = NULL;
    current->B = NULL;
    current->Padre = NULL;
    return current;
  }

  current = arbol;
  for (;;) {
    if (current->r == x) {
      perror("Elemento presente en el arbol\n");
      return arbol;
    }

    if (x < current->r) {
      if (current->A == NULL) {
        break;
      }
      current = current->A;
    } else {
      if (current->B == NULL) {
        break;
      }
      current = current->B;
    }
  }

  if (x < current->r) {
    current->A = malloc(sizeof(SplayTree));
    current->A->r = x;
    current->A->A = NULL;
    current->A->B = NULL;
    current->A->Padre = current;
    return splay(current->A);
  } else {
    current->B = malloc(sizeof(SplayTree));
    current->B->r = x;
    current->B->A = NULL;
    current->B->B = NULL;
    current->B->Padre = current;
    return splay(current->B);
  }

}

void delete(SplayTree* arbol) {
  if (arbol == NULL) {
    return;
  }

  if (arbol->A != NULL) {
    delete(arbol->A);
    arbol->A = NULL;
  }
  
  if (arbol->B != NULL) {
    delete(arbol->B);
    arbol->B = NULL;
  }

  free(arbol);
  return;
}

