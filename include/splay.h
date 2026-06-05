#ifndef SPLAY
#define SPLAY

#define max(a,b) (((a) > (b)) ? (a) : (b))

// Un nodo del SplayTree según la recomendación del paper original
// https://www.cs.cmu.edu/~sleator/papers/self-adjusting.pdf
typedef struct Nodo_splay { // Sería lo que se define como r(A, B)
  int r; // Dato del nodo
  struct Nodo_splay* A; // Arbol izquierdo
  struct Nodo_splay* B; // Arbol derecho
  struct Nodo_splay* Padre; // Puntero al padre
} SplayTree;

// arbol: Puntero al arbol al que se le consulta su izq, función
// se define para no tener que chequear si es que arbol es nulo
// cada vez. izq(NULL) == NULL
SplayTree* izq_spl(SplayTree* arbol);

// arbol: Puntero al arbol al que se le consulta su der, función
// se define para no tener que chequear si es que arbol es nulo
// cada vez. der(NULL) == NULL
SplayTree* der_spl(SplayTree* arbol);

// arbol: Puntero al arbol al que se le consulta su pad, función
// se define para no tener que chequear si es que arbol es nulo
// cada vez. pad(NULL) == NULL
SplayTree* pad_spl(SplayTree* arbol);

// arbol: puntero a la raiz del arbol al que se le va a hacer
// la operación zig (rotación a la derecha).
// Se asume que en este arbol el lado izquierdo no es nulo.
// Retorna NULL si es que es el caso y la nueva raiz sinó
SplayTree* zig_spl(SplayTree* arbol);

// arbol: puntero a la raiz del arbol al que se le va a hacer
// la operación zag (rotación a la izquierda).
// Se asume que en este arbol el lado derecho no es nulo.
// Retorna NULL si es que es el caso y la nueva raiz sinó
SplayTree* zag_spl(SplayTree* arbol);


SplayTree* zigzig_spl(SplayTree* arbol);
SplayTree* zagzag_spl(SplayTree* arbol);
SplayTree* zigzag_spl(SplayTree* arbol);
SplayTree* zagzig_spl(SplayTree* arbol);

SplayTree* splay_spl(SplayTree* arbol);

// arbol: El arbol donde se busca el elemento
// x: El elemento a buscar
// busca el elemento x en arbol y retorna un puntero a el,
// si es que no se encuentra retorna NULL
SplayTree* search_spl(SplayTree* arbol, int x);

// arbol: puntero al arbol donde se inserta el elemento
// x: El elemento a instertar
// inserta el elemento x en el arbol, x no puede estar ya en
// el arbol. Mantiene la invariante del balance factor y
// recalcula las alturas de los subarboles tocados 
SplayTree* insert_spl(SplayTree* arbol, int x);


void delete_spl(SplayTree* arbol);

#endif
