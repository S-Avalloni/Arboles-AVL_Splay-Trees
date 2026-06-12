#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/trees.h"

#define c 5

typedef int (*Generador)(unsigned int N);

enum Tipo_Lista {
  ORDENADO,
  NO_ORDENADO
};

int compare_asc(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

// Se va a tomar lambda = log(31/32) ~ 0.014 ya que así
// se facilita el calculo de la probabilidad y el sampleo
// de los datos.
// Esto implica que exp(-lambda) = 31/32


// La distribución que nos dan es una geometrica de
// parametro 1-exp(-lambda) = 1/32
int geom(unsigned int N) {
  unsigned int conteo;
  do {
    conteo = 0;
    // bernoulli(1/32) hasta que haya un acierto
    while ((rand()&0b11111) != 0b11111) {
      conteo++;
    }
    
  } while (conteo>=N); // Se resamplea si es que se pasa de N

  return conteo;

}

int unif(unsigned int N) {
  unsigned int resultado;
  do {
    resultado = rand();
  } while (resultado>=N);
  return resultado;
}

// archivo: archivo abierto desde el que se leen 2^p elementos
// el archivo debe tener por lo menos ese tamaño
int test(FILE *archivo, unsigned int N, Generador generador, enum Tipo_Lista tipo_lista) {
  
  unsigned int* elementos = malloc(sizeof(unsigned int)*N);
  if (elementos == NULL) {
    perror("Error en la creación de la lista en ram\n");
    return 1;
  }

  printf("Se hace el malloc\n");

  unsigned int resultado = fread(elementos, sizeof(unsigned int), N, archivo);
  
  if (resultado != N) {
    perror("Lectura de los elementos tuvo un error\n");
    free(elementos);
    return 1;
  }

  printf("Se lee la lista\n");

  switch (tipo_lista) {
    case ORDENADO: {
      qsort(elementos, resultado, sizeof(unsigned int), compare_asc);
      break;
    }
    case NO_ORDENADO:
      break;
  }

  printf("Se deja la lista como es pedido\n");

  clock_t start, end;
  double cpu_time_used;

  printf("Inserción\n");

  Avl* cabeza_avl = NULL;

  start = clock();
  for (unsigned int i = 0; i < N; i++) {
    cabeza_avl = insert(cabeza_avl, elementos[generador(N)]);
  }
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f segundos Avl\n", cpu_time_used);

  SplayTree* cabeza_spl = NULL;

  start = clock();
  for (unsigned int i = 0; i < N; i++) {
    cabeza_spl = insert(cabeza_spl, elementos[generador(N)]);
  }
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f segundos SplayTree\n", cpu_time_used);

  /*
  printf("\nBusqueda\n");
  
  start = clock();
  for (int i = 0; i<10*c*(1<<p); i++) {
    cabeza_avl = search(cabeza_avl, elementos[rand()&mask]);
  }
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f segundos Avl\n", cpu_time_used);
  */
  
  free(elementos);
  delete(cabeza_avl);
  delete(cabeza_spl);

  return 0;
}

int main() {

  srand(time(NULL));
  char title[20];

  snprintf(title, 19, "./data/dataset_%d", 10);
  FILE *archivo = fopen(title, "rb");
  if (archivo == NULL) {
    perror("Hubo un error al abrir el archivo\n");
    return 1;
  }

  fseek(archivo, 0, SEEK_END);
  long t = ftell(archivo)/sizeof(unsigned int);
  int size = 1<<10;
  printf("tamaño: %ld\nN: %d\n", t, size);

  fseek(archivo, 0, SEEK_SET);
  test(archivo, size, unif, (enum Tipo_Lista)NO_ORDENADO);

  /*
  for (int p = 10; p <= 14; p++) {
    snprintf(title, 19, "./data/dataset_%d", p);
    FILE *archivo = fopen(title, 'rb');
    int size = 1<<p;

    test(archivo, p);

  }
  */
  return 1;
}