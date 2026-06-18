#ifndef TREES_H
#define TREES_H

#include "./avl.h"
#include "./splay.h"

// Escape codes para poder poner colores en linea de comandos
#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

// Funciones genericas para facilitar el uso en los
// codigos de src/. Revisar comentarios especificos
// en avl.h o splay.h
#define zig(arbol) _Generic((arbol), \
  Avl*: zig_avl, \
  SplayTree*: zig_spl \
)(arbol)

#define zag(arbol) _Generic((arbol), \
  Avl*: zag_avl, \
  SplayTree*: zag_spl \
)(arbol)

/*
No fue necesario implementar el generico de ninguna
rotación doble ya que Avl fue hecho sin estas implementaciones
*/

#define search(arbol, i) _Generic((arbol), \
  Avl*: search_avl, \
  SplayTree*: search_spl \
)(arbol, i)

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

// Función de comparación de unsigned int para
// utilizar en qsort de una lista con unsigned
// int, -1 si a<b, 1 si a>b, 0 si a==b
int compare_asc(const void *a, const void *b);

typedef int (*Generador)(unsigned int N);

// Habiendo elegido un buen lambda esta es una geometrica
// de prametro 1/32 en el rango [0, N-1]
// Por rand(), N debe ser menor o igual a 2^31
int geom(unsigned int N);

// Variable aleatoria uniforme en rango [0, N-1]
// implementado con rand() por lo que N debe ser
// menor o igual a 2^31 para que tenga sentido
int unif(unsigned int N);

// Función identidad con la misma forma que los otros
// generadores para facilitar la toma de numeros en orden
int seq(unsigned int N);


#endif