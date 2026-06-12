#include <stdlib.h>
#include <stdio.h>
#include "splay.h"

SplayTree* izq_spl(SplayTree* arbol) {
  if (arbol == NULL || arbol->A == NULL) {
    return NULL;
  }

  return arbol->A;
}

SplayTree* der_spl(SplayTree* arbol) {
  if (arbol == NULL || arbol->B == NULL) {
    return NULL;
  }

  return arbol->B;
}

SplayTree* pad_spl(SplayTree* arbol) {
  if (arbol == NULL || arbol->Padre == NULL) {
    return NULL;
  }

  return arbol->Padre;
}


SplayTree* zig_spl(SplayTree* arbol) {
  if (izq_spl(arbol) == NULL) {
    perror("No se puede hacer zig con nodo nulo o nodo izquierdo nulo\n");
    return arbol;
  }
  
  if (pad_spl(arbol) != NULL) {
    if (pad_spl(arbol)->A == arbol) {
      pad_spl(arbol)->A = arbol->A;
    } else {
      pad_spl(arbol)->B = arbol->A;
    }
  }

  SplayTree* temp;
  arbol->A->Padre = pad_spl(arbol);
  if (der_spl(arbol->A) != NULL) {
    arbol->A->B->Padre = arbol;
  }

  temp = arbol->A->B;
  arbol->A->B = arbol;
  arbol->Padre = arbol->A;
  arbol->A = temp;

  return arbol->Padre;
}

SplayTree* zag_spl(SplayTree* arbol) {
  if (der_spl(arbol) == NULL) {
    perror("No se puede hacer zag con nodo nulo o nodo derecho nulo\n");
    return arbol;
  }
  
  if (pad_spl(arbol) != NULL) {
    if (pad_spl(arbol)->A == arbol) {
      pad_spl(arbol)->A = arbol->B;
    } else {
      pad_spl(arbol)->B = arbol->B;
    }
  }

  SplayTree* temp;
  arbol->B->Padre = pad_spl(arbol);
  if (izq_spl(arbol->B) != NULL) {
    arbol->B->A->Padre = arbol;
  }

  temp = arbol->B->A;
  arbol->B->A = arbol;
  arbol->Padre = arbol->B;
  arbol->B = temp;

  return arbol->Padre;

}

SplayTree* zigzig_spl(SplayTree* arbol) {
  return zig_spl(zig_spl(arbol));
}

SplayTree* zagzag_spl(SplayTree* arbol) {
  return zag_spl(zag_spl(arbol));
}

SplayTree* zigzag_spl(SplayTree* arbol) {
  zag_spl(arbol->A);
  return zig_spl(arbol);
}

SplayTree* zagzig_spl(SplayTree* arbol) {
  zig_spl(arbol->B);
  return zag_spl(arbol);
}

SplayTree* splay_spl(SplayTree* arbol) {

  // Asumimos que estamos en el arbol que queremos
  // llevar hasta la raiz

  while (pad_spl(pad_spl(arbol))!=NULL) {

    if (arbol->r < pad_spl(pad_spl(arbol))->r) { // a la izquierda del abuelo
      if (arbol->r < pad_spl(arbol)->r) { // a la izquierda de su padre
        // arbol->A->A == arbol;
        zigzig_spl(pad_spl(pad_spl(arbol)));
      } else {
        zigzag_spl(pad_spl(pad_spl(arbol)));
      }
    } else {
      if (arbol->r < pad_spl(arbol)->r) {
        zagzig_spl(pad_spl(pad_spl(arbol)));
      } else {
        zagzag_spl(pad_spl(pad_spl(arbol)));
      }
    }
  }

  if (pad_spl(arbol) == NULL) {
    return arbol;
  }
  if (pad_spl(arbol->Padre) == NULL) {
    if (pad_spl(arbol)->A == arbol) {
      return zig_spl(arbol->Padre);
    } else {
      return zag_spl(arbol->Padre);
    }
  }

  return arbol;
}

SplayTree* search_spl(SplayTree* arbol, unsigned int x) {
  
  if (arbol == NULL) {
    perror("Busqueda en un arbol vacío\n");
    return arbol;
  }
  SplayTree* current = arbol;

  for (;;) {
    if (current->r == x) {
      break;
    } else if (x < current->r) {
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

  return splay_spl(current);
}

SplayTree* insert_spl(SplayTree* arbol, unsigned int x) {
  
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
    return splay_spl(current->A);
  } else {
    current->B = malloc(sizeof(SplayTree));
    current->B->r = x;
    current->B->A = NULL;
    current->B->B = NULL;
    current->B->Padre = current;
    return splay_spl(current->B);
  }

}

void preorder_spl(SplayTree* arbol) {
  if (arbol->A != NULL) {
    preorder_spl(arbol->A);
  }
  printf("%d\n", arbol->r);

  if (arbol->B != NULL) {
    preorder_spl(arbol->B);
  } 

}

void delete_spl(SplayTree* arbol) {
  if (arbol == NULL) {
    return;
  }

  if (arbol->A != NULL) {
    delete_spl(arbol->A);
    arbol->A = NULL;
  }
  
  if (arbol->B != NULL) {
    delete_spl(arbol->B);
    arbol->B = NULL;
  }

  free(arbol);
  return;
}

