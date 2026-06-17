#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/trees.h"

#define c 3

#define N 0b10000000000000000000000000

int seq_access() {


  FILE *archivo = fopen("./data/dataset_25", "rb");
  if (archivo == NULL) {
    perror("No se pudo abrir el dataset\n");
    return 1;
  }

  Avl *sat_avl = NULL;
  SplayTree *sat_spl = NULL;

  unsigned int *elementos = malloc(sizeof(unsigned int)*N);
  unsigned int *busqueda = malloc(sizeof(unsigned int)*N);
  
  if (elementos == NULL) {
    perror("Error en la creación de la lista en ram\n");
    return 1;
  }

  if (busqueda == NULL) {
    perror("Error en la creación de la copia\n");
    free(elementos);
    return 1;
  }

  
  unsigned int resultado = fread(elementos, sizeof(unsigned int), N, archivo);

  if (resultado != N) {
    perror("Lectura de los elementos tuvo un error\n");
    free(busqueda);
    free(elementos);
    return 1;
  }

  memcpy(busqueda, elementos, sizeof(unsigned int)*N);

  qsort(busqueda, N, sizeof(unsigned int), compare_asc);

  pid_t pid = fork();

  if (pid == 0) {

    AvlContext* ctx_avl = init_ctx_avl(N);

    clock_t start_avl, end_avl;
    double cpu_time_used_avl=0;

    start_avl = clock();
    for (int i = 0; i<N; i++) {
      sat_avl = insert(ctx_avl, sat_avl, elementos[i]);
    }
    end_avl = clock();
    printf("%f segundos construcción avl\n", ((double) (end_avl - start_avl)) / CLOCKS_PER_SEC);

    for (int m = 0; m < N/10; m+= N/100) {
      start_avl = clock();
      for (int j = 0; j<N/100; j++) {
        search(sat_avl, busqueda[j+m]);
      }
      end_avl = clock();
      cpu_time_used_avl += ((double) (end_avl - start_avl)) / CLOCKS_PER_SEC;
      printf("%f segundos avl m: %d\n", cpu_time_used_avl, m);
    }

    delete(ctx_avl);
  } else {

    SplayTreeContext* ctx_spl = init_ctx_spl(N);
    clock_t start_spl, end_spl;
    double cpu_time_used_spl=0;

    start_spl = clock();
    for (int i = 0; i<N; i++) {
      sat_spl = insert(ctx_spl, sat_spl, elementos[i]);
    }
    end_spl = clock();
    printf("%f segundos construcción spl\n", ((double) (end_spl - start_spl)) / CLOCKS_PER_SEC);

    for (int m = 0; m < N/10; m+= N/100) {
      start_spl = clock();
      for (int j = 0; j<N/100; j++) {
        sat_spl = search(sat_spl, busqueda[j+m]);
      }
      end_spl = clock();

      cpu_time_used_spl += ((double) (end_spl - start_spl)) / CLOCKS_PER_SEC;
      printf("%f segundos spl m: %d\n", cpu_time_used_spl, m);
    }

    delete(ctx_spl);
  }

  

  free(elementos);
  free(busqueda);

  if (pid == 0) {
    _exit(0);
  } else {
    waitpid(pid, NULL, 0);
  }

  return 0;
}

int working_set() {

  FILE *archivo = fopen("./data/dataset_25", "rb");
  if (archivo == NULL) {
    perror("No se pudo abrir el dataset\n");
    return 1;
  }

  unsigned int *elementos = malloc(sizeof(unsigned int)*N);
  
  if (elementos == NULL) {
    perror("Error en la creación de la lista en ram\n");
    return 1;
  }
  
  unsigned int resultado = fread(elementos, sizeof(unsigned int), N, archivo);

  if (resultado != N) {
    perror("Lectura de los elementos tuvo un error\n");
    free(elementos);
    return 1;
  }

  fclose(archivo);


  unsigned int *W_set = malloc(sizeof(unsigned int)*(1000000));
  if (W_set == NULL) {
    perror("No se pudo alocar memoria para el Working set");
    return 1;
  }

  for (int i = 0; i < 1000000; i++) {
    W_set[i] = elementos[unif(N)];
  }
  
  int W = 10;

  clock_t ahora = clock();
  
  pid_t pid = fork();

  srand(ahora);

  if (pid != 0) { // Padre (Splay)
    SplayTree* arbol_og_spl = NULL;
    SplayTreeContext* ctx_og_spl = init_ctx_spl(N);

    for (int j = 0; j<N; j++) {
      arbol_og_spl = insert(ctx_og_spl, arbol_og_spl, elementos[j]);
    }

    SplayTree* arbol_spl = NULL;
    SplayTreeContext* ctx_spl = init_ctx_spl(N);

    clock_t start_spl, end_spl;
    double cpu_time_used_spl;

    for(int exp = 1; exp <= 6; exp++) {
      
      arbol_spl = NULL;
      copy(ctx_spl, ctx_og_spl, &arbol_spl, arbol_og_spl);


      start_spl = clock();
      for (int j = 0; j < 10*c*N; j++) {
        arbol_spl = search(arbol_spl, W_set[unif(W)]);
      }
      end_spl = clock();
      cpu_time_used_spl = ((double) (end_spl - start_spl)) / CLOCKS_PER_SEC;

      printf("%f segundos busqueda spl W: 10^%d\n", cpu_time_used_spl, exp);
      
      W *= 10;
    }

    delete(ctx_og_spl);
    delete(ctx_spl);

  } else {
    Avl* arbol_og_avl = NULL;
    AvlContext* ctx_og_avl = init_ctx_avl(N);

    for (int j = 0; j<N; j++) {
      arbol_og_avl = insert(ctx_og_avl, arbol_og_avl, elementos[j]);
    }

    Avl* arbol_avl = NULL;
    AvlContext* ctx_avl = init_ctx_avl(N);

    clock_t start_avl, end_avl;
    double cpu_time_used_avl;

    for(int exp = 1; exp <= 6; exp++) {

      arbol_avl = NULL;
      copy(ctx_avl, ctx_og_avl, &arbol_avl, arbol_og_avl);


      start_avl = clock();
      for (int j = 0; j < 10*c*N; j++) {
        search(arbol_avl, W_set[unif(W)]);
      }
      end_avl = clock();
      cpu_time_used_avl = ((double) (end_avl - start_avl)) / CLOCKS_PER_SEC;

      printf("%f segundos busqueda avl W: 10^%d\n", cpu_time_used_avl, exp);      
    
      W *= 10;
    }

    delete(ctx_og_avl);
    delete(ctx_avl);
  }

  free(W_set);
  free(elementos);

  if (pid != 0) {
    waitpid(pid, NULL, 0);
  } else {
    exit(0);
  }

  return 0;
}

int main() {
  if (seq_access() == 1) {
    perror("Hubo un error al hacer el experimento de Sequential Access Theorem");
    return 1;
  };

  if (working_set() == 1) {
    perror("Hubo un error al hacer el experimento de Working Set Theorem");
    return 1;
  }
}