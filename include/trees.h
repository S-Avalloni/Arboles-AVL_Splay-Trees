#ifndef TREES_H
#define TREES_H

#include <./avl.h>
#include <./splay.h>

#define zig(arbol) _Generic((arbol), \
  Avl*: zig_avl, \
  SplayTree*: zig_spl \
)(arbol)

#define zag(arbol) _Generic((arbol), \
  Avl*: zag_avl, \
  SplayTree*: zag_spl \
)(arbol)

#define zigzig(arbol) _Generic((arbol), \
  Avl*: zigzig_avl, \
  SplayTree*: zigzig_spl \
)(arbol)

#define zagzag(arbol) _Generic((arbol), \
  Avl*: zagzag_avl, \
  SplayTree*: zagzag_spl \
)(arbol)

#define zigzag(arbol) _Generic((arbol), \
  Avl*: zigzag_avl, \
  SplayTree*: zigzag_spl \
)(arbol)

#define zagzig(arbol) _Generic((arbol), \
  Avl*: zagzig_avl, \
  SplayTree*: zagzig_spl \
)(arbol)

#define search(arbol, i) _Generic((arbol), \
  Avl*: search_avl, \
  SplayTree*: search_spl \
)(arbol, i)

#define insert(arbol, i) _Generic((arbol), \
  Avl*: insert_avl, \
  SplayTree*: insert_spl \
)(arbol, i)

#define preorder(arbol) _Generic((arbol), \
  Avl*: preorder_avl, \
  SplayTree*: preorder_spl \
)(arbol)

#define delete(arbol, i) _Generic((arbol), \
  Avl*: delete_avl, \
  SplayTree*: delete_spl \
)(arbol, i)

typedef enum {
  SPLAY,
  AVL
} Tree_Type;

#endif