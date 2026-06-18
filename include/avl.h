#ifndef AVL_H
#define AVL_H

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct Nodo_Avl { // Sería lo que se define como r(A, B)
  unsigned int r; // Dato del nodo
  struct Nodo_Avl* A; // Arbol izquierdo
  struct Nodo_Avl* B; // Arbol derecho
  unsigned int altura;
} Avl;

// Lista de Avl's indice del ultimo y la capacidad maxima
// de esta lista, esto para mejorar el cache locality y tener 
// que hacer un solo malloc por arbol
typedef struct Memoria_avl {
  Avl* pool;
  int idx;
  int capacity;
} AvlContext;

// Se inicializa la memoria que va a contener al arbol,
// esta funcion retorna un puntero al contexto donde se
// va a encontrar el arbol.
// Size debe ser suficientemente grande para almacenar
// todos los nodos (i.e. size > numero de nodos maximos)
AvlContext* init_ctx_avl(unsigned int size);

// arbol: puntero a la raiz del arbol al que se le consulta
// su altura.
// Hace el chequeo de si es que el puntero es nulo y retorna
// 0 o arbol->altura correspondientemente.
unsigned int altura_avl(Avl* arbol);

// arbol: puntero al arbol al que se le calcula su balance factor
// 0 si el puntero es nulo, H(A)-H(B) para x(A, B) segun la
// notación estandar 
int balance_factor_avl(Avl* arbol);

// arbol: puntero a la raiz del arbol al que se le va a hacer
// la operación zig (rotación a la derecha).
// Se asume que en este arbol el lado izquierdo no es nulo.
// Retorna NULL si es que es el caso y la nueva raiz sinó
Avl* zig_avl(Avl* arbol);

// arbol: puntero a la raiz del arbol al que se le va a hacer
// la operación zag (rotación a la izquierda).
// Se asume que en este arbol el lado derecho no es nulo.
// Retorna NULL si es que es el caso y la nueva raiz sinó
Avl* zag_avl(Avl* arbol);

// arbol: El arbol donde se busca el elemento
// x: El elemento a buscar
// busca el elemento x en arbol y retorna un puntero a el,
// si es que no se encuentra retorna NULL
Avl* search_avl(Avl* arbol, unsigned int x);

// arbol: puntero al arbol donde se inserta el elemento
// x: El elemento a instertar
// inserta el elemento x en el arbol, x no puede estar ya en
// el arbol. Mantiene la invariante del balance factor y
// recalcula las alturas de los subarboles tocados.
// Retorna el puntero a la raiz, normalmente va a ser el mismo
// valor pero es necesario en caso de que se modifique la raiz
Avl* insert_avl(AvlContext* ctx, Avl* arbol, unsigned int x);

// ctx: contexto de entrada
// out: contexto de salida
// nueva_raiz: posición de memoria del puntero donde se quiere poner la raíz 
//              del contexto de entrada
// raiz_original: puntero a la raiz del arbol del contexto ctx
// Hace una copia de todo el contexto del arbol, O(N) en vez de O(Nlog(N))
// que sería volver a insertar todo
// Todos los punteros se arreglan para no apuntar a las posiciones originales sinó a las
// correspondientes relativas a la posición de out
int copy_avl(AvlContext* out, AvlContext* ctx, Avl** nueva_raiz, Avl* raiz_original);

// arbol: puntero al nodo desde el que se quiere realizar la 
//        operación
// imprime en orden los valores a los que se puede llegar 
// desde el nodo arbol
void inorder_avl(Avl* arbol);

// ctx: contexto que se quiere liberar de memoria
// libera la lista pool del contexto, libera el puntero
// a ctx y deja ambos punteros en NULL
void delete_avl(AvlContext* ctx);

#endif