#ifndef SPLAY_H
#define SPLAY_H

#define max(a,b) (((a) > (b)) ? (a) : (b))

// Un nodo del SplayTree según la recomendación del paper original
// https://www.cs.cmu.edu/~sleator/papers/self-adjusting.pdf
typedef struct Nodo_splay { // Sería lo que se define como r(A, B)
  unsigned int r; // Dato del nodo
  struct Nodo_splay* A; // Arbol izquierdo
  struct Nodo_splay* B; // Arbol derecho
  struct Nodo_splay* Padre; // Puntero al padre
} SplayTree;

// Lista de SplayTree's indice del ultimo y la capacidad maxima
// de esta lista, esto para mejorar el cache locality y tener 
// que hacer un solo malloc por arbol
typedef struct Memoria_splay {
  SplayTree* pool;
  int idx;
  int capacity;
} SplayTreeContext;

// Se inicializa la memoria que va a contener al arbol,
// esta funcion retorna un puntero al contexto donde se
// va a encontrar el arbol.
// Size debe ser suficientemente grande para almacenar
// todos los nodos (i.e. size > numero de nodos maximos)
SplayTreeContext* init_ctx_spl(unsigned int size);

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

// Rotaciones dobles para SplayTree según está especificado en
// el enunciado de la tarea
// arbol: puntero al nodo sobre el que se va a hacer la rotación
// return: puntero al nodo que queda en el punto original
SplayTree* zigzig_spl(SplayTree* arbol);
SplayTree* zagzag_spl(SplayTree* arbol);
SplayTree* zigzag_spl(SplayTree* arbol);
SplayTree* zagzig_spl(SplayTree* arbol);

// arbol: puntero al nodo que se quiere llevar a la raiz
// retorna un puntero al nuevo nodo que va a quedar en la raiz
// del arbol (en nuestro caso es el mismo valor que el input 
// pero por consistencia ante las otras funciones es mejor 
// mantenerlo así)
SplayTree* splay_spl(SplayTree* arbol);

// arbol: El arbol donde se busca el elemento
// x: El elemento a buscar
// busca el elemento x en arbol y retorna un puntero a el,
// si es que no se encuentra retorna NULL
SplayTree* search_spl(SplayTree* arbol, unsigned int x);

// arbol: puntero al arbol donde se inserta el elemento
// x: El elemento a instertar
// inserta el elemento x en el arbol, x no puede estar ya en
// el arbol. Mantiene la invariante del balance factor y
// recalcula las alturas de los subarboles tocados 
SplayTree* insert_spl(SplayTreeContext* ctx, SplayTree* arbol, unsigned int x);

// ctx: contexto de entrada
// out: contexto de salida
// nueva_raiz: posición de memoria del puntero donde se quiere poner la raíz 
//              del contexto de entrada
// raiz_original: puntero a la raiz del arbol del contexto ctx
// Hace una copia de todo el contexto del arbol, O(N) en vez de O(Nlog(N))
// que sería volver a insertar todo
// Todos los punteros se arreglan para no apuntar a las posiciones originales sinó a las
// correspondientes relativas a la posición de out
int copy_spl(SplayTreeContext* out, SplayTreeContext* ctx, SplayTree** nueva_raiz, SplayTree* raiz_original);

// arbol: puntero al nodo desde el que se quiere realizar la 
//        operación
// imprime en orden los valores a los que se puede llegar 
// desde el nodo arbol
void inorder_spl(SplayTree* arbol);

// ctx: contexto que se quiere liberar de memoria
// libera la lista pool del contexto, libera el puntero
// a ctx y deja ambos punteros en NULL
void delete_spl(SplayTreeContext* ctx);

#endif
