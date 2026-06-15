#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/trees.h"

#define c 5

#define N 0b10000000000000000000000000

int compare_asc(const void *a, const void *b) {
    unsigned int val_a = *(const unsigned int *)a;
    unsigned int val_b = *(const unsigned int *)b;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}


int seq_access() {


  FILE *archivo = fopen("./data/dataset_25", "rb");
  if (archivo == NULL) {
    perror("No se pudo abrir el dataset\n");
    return 1;
  }

  Avl *sat_avl = NULL, *wst_avl = NULL;
  SplayTree *sat_spl = NULL, *wst_spl = NULL;

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
    clock_t start_avl, end_avl;
    double cpu_time_used_avl=0;

    for (int i = 0; i<N; i++) {
      sat_avl = insert(sat_avl, elementos[i]);
    }

    for (int m = 0; m < N/10; m+= N/100) {
      start_avl = clock();
      for (int j = 0; j<N/100; j++) {
        search(sat_avl, busqueda[j+m]);
      }
      end_avl = clock();
      cpu_time_used_avl += ((double) (end_avl - start_avl)) / CLOCKS_PER_SEC;
      printf("%f segundos avl m: %d\n", cpu_time_used_avl, m);
    }
  } else {
    clock_t start_spl, end_spl;
    double cpu_time_used_spl=0;

    for (int i = 0; i<N; i++) {
      sat_spl = insert(sat_spl, elementos[i]);
    }

    for (int m = 0; m < N/10; m+= N/100) {
      start_spl = clock();
      for (int j = 0; j<N/100; j++) {
        sat_spl = search(sat_spl, busqueda[j+m]);
      }
      end_spl = clock();

      cpu_time_used_spl += ((double) (end_spl - start_spl)) / CLOCKS_PER_SEC;
      printf("%f segundos spl m: %d\n", cpu_time_used_spl, m);
    }
  }

  
  delete(sat_avl);
  delete(sat_spl);
  delete(wst_avl);
  delete(wst_spl);

  free(elementos);
  free(busqueda);

  if (pid == 0) {
    exit(0);
  } else {
    waitpid(pid, NULL, 0);
  }

  return 0;
}

int main() {
  return 0;
}