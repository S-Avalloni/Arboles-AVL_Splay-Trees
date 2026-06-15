#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/trees.h"

#define c 5

enum Tipo_Lista {
  ORDENADO,
  NO_ORDENADO
};

// archivo: archivo abierto desde el que se leen N elementos
// el archivo debe tener por lo menos ese tamaño
int test(FILE *archivo, unsigned int N, enum Tipo_Lista tipo_lista, Generador generador) {
  
  unsigned int* elementos = malloc(sizeof(unsigned int)*N);
  if (elementos == NULL) {
    perror("Error en la creación de la lista en ram\n");
    return 1;
  }

  #ifdef VERBOSO
  printf("Se hace el malloc\n");
  #endif

  unsigned int resultado = fread(elementos, sizeof(unsigned int), N, archivo);
  
  if (resultado != N) {
    perror("Lectura de los elementos tuvo un error\n");
    free(elementos);
    return 1;
  }
  
  #ifdef VERBOSO
  printf("Se lee la lista\n");
  #endif
  Generador vista_elementos = seq;
  unsigned int i;

  unsigned int *j = malloc(sizeof(unsigned int));
  switch (tipo_lista) {
    case ORDENADO: {
      qsort(elementos, resultado, sizeof(unsigned int), compare_asc);
      vista_elementos = seq;
      free(j);
      j = &i; 
      break;
    }
    case NO_ORDENADO:
      vista_elementos = unif;
      *j = N;      
      break;
  }

  #ifdef VERBOSO
  printf("Se deja la lista como es pedido\n");
  #endif

  clock_t start, end;
  double cpu_time_used;

  pid_t pid = fork();

  if (pid != 0) { // Padre

    AvlContext* ctx_avl = init_ctx_avl(N);


    #ifdef VERBOSO
    printf(BLUE("Inserción") "\n");
    #endif

    Avl* cabeza_avl = NULL;

    start = clock();
    for (i = 0; i < N; i++) {
      cabeza_avl = insert(ctx_avl, cabeza_avl, elementos[vista_elementos(*j)]);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(BLUE("%f segundos Avl") "\n", cpu_time_used);
    
    #ifdef VERBOSO
    printf(GREEN("Busqueda") "\n");
    #endif

    start = clock();
    for (i=0; i < ((unsigned int)10*c*N); i++) {
      search_avl(cabeza_avl, elementos[generador(N)]);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(GREEN("%f segundos Avl") "\n", cpu_time_used);

    delete(ctx_avl);
  } else { // Hijo

    SplayTreeContext* ctx_spl = init_ctx_spl(N);
    SplayTree* cabeza_spl = NULL;

    start = clock();
    for (i = 0; i < N; i++) {
      cabeza_spl = insert(ctx_spl, cabeza_spl, elementos[vista_elementos(*j)]);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(BLUE("%f segundos Splay") "\n", cpu_time_used);
    

    start = clock();
    for (i=0; i < ((unsigned int)10*c*N); i++) {
      cabeza_spl = search(cabeza_spl, elementos[generador(N)]);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(GREEN("%f segundos Splay") "\n", cpu_time_used);

    delete(ctx_spl);
  }
  
  
  switch (tipo_lista) {
    case ORDENADO:
      break;
    case NO_ORDENADO:
      free(j);
      break;
  }

  free(elementos);

  
  
  if (pid != 0) { // Padre
    waitpid(pid, NULL, 0);
  } else { // Hijo
    exit(0);
  }
  
  return 0;
}

int main() {

  srand(time(NULL));
  char title[20];
  
  for (int p = 10; p <= 14; p++) {
    snprintf(title, 19, "./data/dataset_%d", p);
    FILE *archivo = fopen(title, "rb");

    if (archivo == NULL) {
      perror("Hubo un error al abrir el archivo\n");
      return 1;
    }

    unsigned int size = 1<<p;
    printf("\nN=1<<%d\n", p);

    printf("Inserción aleatoria, búsqueda uniforme:\n");
    fseek(archivo, 0, SEEK_SET);
    test(archivo, size, NO_ORDENADO, unif);

    printf("Inserción aleatoria, búsqueda sesgada:\n");
    fseek(archivo, 0, SEEK_SET);
    test(archivo, size, NO_ORDENADO, geom);

    printf("Inserción ordenada, búsqueda uniforme:\n");
    fseek(archivo, 0, SEEK_SET);
    test(archivo, size, ORDENADO, unif);

    printf("Inserción ordenada, búsqueda sesgada:\n");
    fseek(archivo, 0, SEEK_SET);
    test(archivo, size, ORDENADO, geom);

  }
  
  return 0;
}