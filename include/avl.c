#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"

AvlContext* init_ctx_avl(unsigned int size) {
  AvlContext* ctx = malloc(sizeof(AvlContext));
  ctx->pool = malloc(sizeof(Avl) * size);
  ctx->idx = 0;
  ctx->capacity = size;
  return ctx;
}

static Avl* alloc_avl(AvlContext* ctx) {
  return &ctx->pool[ctx->idx++];
}

unsigned int altura_avl(Avl* arbol) {
  if (arbol == NULL) {
    return 0;
  }

  return arbol->altura;
}

int balance_factor_avl(Avl* arbol) {
  if (arbol == NULL) {
    return 0;
  }

  // Puede ser bien desastrozo si es que alguno es muy grande
  // y el casteo lo hace negativo pero hay que cruzar los dedos
  return (int)altura_avl(arbol->A) - (int)altura_avl(arbol->B);

}

Avl* zig_avl(Avl* arbol) {
  Avl* nueva_raiz = arbol->A;
  if (nueva_raiz == NULL) {
    #ifdef VERBOSO
    perror("zig: Lado izquierdo del arbol no puede ser nulo\n");
    #endif
    return NULL;
  }
  arbol->A = (nueva_raiz)->B;
  nueva_raiz->B = arbol;
  
  // Debemos recalcular altura de abajo hacia arriba
  arbol->altura = 1 + max(altura_avl(arbol->A), altura_avl(arbol->B));
  nueva_raiz->altura = 1 + max(altura_avl(nueva_raiz->A),altura_avl(nueva_raiz->B));

  return nueva_raiz;
}

Avl* zag_avl(Avl* arbol) {
  Avl* nueva_raiz = arbol->B;
  if (nueva_raiz == NULL) {
    #ifdef VERBOSO
    perror("zag: Lado derecho del arbol no puede ser nulo\n");
    #endif
    return NULL;
  }
  arbol->B = (nueva_raiz)->A;
  nueva_raiz->A = arbol;
  
  // Debemos recalcular altura de abajo hacia arriba
  arbol->altura = 1 + max(altura_avl(arbol->A), altura_avl(arbol->B));
  nueva_raiz->altura = 1 + max(altura_avl(nueva_raiz->A),altura_avl(nueva_raiz->B));

  return nueva_raiz;
}

Avl* search_avl(Avl* arbol, unsigned int x) {
  Avl* current = arbol;

  for(;;) {

    if (current==NULL || current->r == x) {
      return current;
    } else if (current -> r > x) {
      current = current -> A;
    } else {
      current = current -> B;
    }
  }

  return current;
}

Avl* insert_avl(AvlContext* ctx, Avl* arbol, unsigned int x) {
  if (arbol == NULL) {
    
    arbol = alloc_avl(ctx);

    arbol->r = x;
    arbol->A = NULL;
    arbol->B = NULL;
    arbol->altura = 1;
    return arbol;
  } else if (arbol -> r > x) {
    arbol->A = insert_avl(ctx, arbol->A, x);
  } else if (arbol -> r < x){
    arbol->B = insert_avl(ctx, arbol -> B, x);
  } else {
    #ifdef VERBOSO
    perror("No se pueden insertar un elemento repetido\n");
    #endif
    return arbol;
  }


  int bf_root = balance_factor_avl(arbol);
  int bf_A    = balance_factor_avl(arbol->A);
  int bf_B    = balance_factor_avl(arbol->B);

  if (bf_root == 2 && bf_A >= 0) {      // LL
    arbol = zig_avl(arbol);
  } else if (bf_root == -2 && bf_B <= 0) { // RR
    arbol = zag_avl(arbol);
  } else if (bf_root == 2 && bf_A < 0) {  // LR
    arbol->A = zag_avl(arbol->A);
    arbol = zig_avl(arbol);
  } else if (bf_root == -2 && bf_B > 0) { // RL
    arbol->B = zig_avl(arbol->B);
    arbol = zag_avl(arbol);
  }
  
  if (arbol == NULL) {
    #ifdef VERBOSO
    perror("Hubo un error al hacer zig o zag al insertar el valor");
    #endif
    return arbol;
  }


  arbol->altura = 1 + max(altura_avl(arbol->A), altura_avl(arbol->B));


  return arbol;
}

int copy_avl(AvlContext* out, AvlContext* ctx, Avl** nueva_raiz, Avl* raiz_original) {
  if (out->capacity < ctx->capacity) {
    perror("Capacidad de salida menor que la de entrada\n");
    return 1;
  }

  memcpy(out->pool, ctx->pool, sizeof(Avl) * ctx->idx);

  out->idx = ctx->idx;

  int offset = out->pool - ctx->pool;
  for (int i = 0; i < out->idx; i++) {
    Avl* nodo = &out->pool[i];
    if (nodo->A      != NULL) nodo->A      += offset;
    if (nodo->B      != NULL) nodo->B      += offset;
  }

  *nueva_raiz = raiz_original + offset;

  return 0;
}

void inorder_avl(Avl* arbol) {
  if (arbol->A != NULL) {
    inorder_avl(arbol->A);
  }
  printf("%u\n", arbol->r);

  if (arbol->B != NULL) {
    inorder_avl(arbol->B);
  } 

}

void delete_avl(AvlContext* ctx) {
  free(ctx->pool);
  ctx->pool = NULL;
  ctx->idx = 0;
  free(ctx);
  return;
}