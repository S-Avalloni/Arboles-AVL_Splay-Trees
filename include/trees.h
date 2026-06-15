#ifndef TREES_H
#define TREES_H

#include "./avl.h"
#include "./splay.h"

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

#define zig(arbol) _Generic((arbol), \
  Avl*: zig_avl, \
  SplayTree*: zig_spl \
)(arbol)

#define zag(arbol) _Generic((arbol), \
  Avl*: zag_avl, \
  SplayTree*: zag_spl \
)(arbol)

/*
Funciones no implementadas en avl por lo que no
es necesario hacerlas genéricas
#define zigzig(arbol) _Generic((arbol), \
  Avl*: zigzig_avl, \
  SplayTree*: zigzig_spl \
)(arbol)
// 
#define zagzag(arbol) _Generic((arbol), \
  Avl*: zagzag_avl, \
  SplayTree*: zagzag_spl \
)(arbol)
// 
#define zigzag(arbol) _Generic((arbol), \
  Avl*: zigzag_avl, \
  SplayTree*: zigzag_spl \
)(arbol)
// 
#define zagzig(arbol) _Generic((arbol), \
  Avl*: zagzig_avl, \
  SplayTree*: zagzig_spl \
)(arbol)
*/

#define search(arbol, i) _Generic((arbol), \
  Avl*: search_avl, \
  SplayTree*: search_spl \
)(arbol, i)

// inserta el elemento i al arbol y retorna un puntero a la
// cabeza de este
#define insert(ctx, arbol, i) _Generic((ctx), \
  AvlContext*: insert_avl, \
  SplayTreeContext*: insert_spl \
)(ctx, arbol, i)

#define copy(out, ctx, nueva_raiz, raiz_original) _Generic((out), \
  AvlContext*: copy_avl, \
  SplayTreeContext*: copy_spl \
)(out, ctx, nueva_raiz, raiz_original)

#define inorder(arbol) _Generic((arbol), \
  Avl*: inorder_avl, \
  SplayTree*: inorder_spl \
)(arbol)

#define delete(ctx) _Generic((ctx), \
  AvlContext*: delete_avl, \
  SplayTreeContext*: delete_spl \
)(ctx)

int compare_asc(const void *a, const void *b);

typedef int (*Generador)(unsigned int N);

// Se va a tomar lambda = log(31/32) ~ 0.014 ya que así
// se facilita el calculo de la probabilidad y el sampleo
// de los datos.
// Esto implica que exp(-lambda) = 31/32
// La distribución que nos dan es una geometrica de
// parametro 1-exp(-lambda) = 1/32
int geom(unsigned int N);

int unif(unsigned int N);

int seq(unsigned int N);

void to_array(Avl *arbol, unsigned int *lista, int *idx);


#endif