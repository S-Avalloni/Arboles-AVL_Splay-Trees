#ifndef SPLAY
#define SPLAY

typedef struct Nodo_splay { // Sería lo que se define como r(A, B)
  int r; // Dato del nodo
  struct Nodo_splay* A; // Arbol izquierdo
  struct Nodo_splay* B; // Arbol derecho
} SplayTree;


// arbol: puntero a la raiz del arbol al que se le va a hacer
// la operación zig (rotación a la derecha).
// Se asume que en este arbol el lado izquierdo no es nulo.
// Retorna NULL si es que es el caso y la nueva raiz sinó
SplayTree* zig(SplayTree* arbol);

// arbol: puntero a la raiz del arbol al que se le va a hacer
// la operación zag (rotación a la izquierda).
// Se asume que en este arbol el lado derecho no es nulo.
// Retorna NULL si es que es el caso y la nueva raiz sinó
SplayTree* zag(SplayTree* arbol);

// arbol: El arbol donde se busca el elemento
// x: El elemento a buscar
// busca el elemento x en arbol y retorna un puntero a el,
// si es que no se encuentra retorna NULL
SplayTree* search(SplayTree* arbol, int x);

// arbol: puntero al arbol donde se inserta el elemento
// x: El elemento a instertar
// inserta el elemento x en el arbol, x no puede estar ya en
// el arbol. Mantiene la invariante del balance factor y
// recalcula las alturas de los subarboles tocados 
int insert(SplayTree* arbol, int x);




#endif