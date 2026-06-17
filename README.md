# Árboles AVL vs Splay Trees

Esta tarea se hizo con el objetivo de comprar los comportamientos asintóticos de las estructuras de datos Splay Tree y Avl Tree, esto mediante la medición de la creación de estos y busqueda sobre estos de manera aleatoria y luego en la comprobación de Working Set Theorem y Sequential Access Theorem. 

## Estructura del proyecto

```
T2/
│
├── include/
│ ├── avl.h
│ ├── avl.c 	# Header y definiciones pertinentes a arboles Avl
│ ├── splay.h
│ ├── splay.c	# Header y definiciones pertinentes a arboles Splay
│ ├── trees.h
│ └── trees.c	# Header y definiciones genericas para ambos arboles
│
├── src/
│ ├── base.c
│ ├── const.c
│ └── experimentos.c
│
├── data/ # Carpeta donde quedan los dataset aleatorios para la creación de los arboles
│
├── build/ # Carpeta de salida de los archivos .o y ejecutables
││
├── Makefile # Instrucciones para compilar y ejecutar los archivos
└── README.md # Este archivo
```

## Compilación

Para compilar todos los programas se debe ejecutar el comando

```bash
make build
```
Este comando generará 3 ejecutables y 3 archivos objeto en la carpeta `./build/`:

- `const`: Crea los 5 dataset pedidos de tamaños $2^i$ con $i\in\{10, 11, 12, 13, 14, 25\}$
- `base`: Ejecuta y mide los tiempos pedidos en la sección 7.2 del enunciado
- `experimentos`: Ejecuta y mide el desempeño de las estructuras frente a los escenarios descritos en la sección 7.3.1 del enunciado

En el caso de querer compilar un ejecutable especifico las opciones que se dan son respectivamente:

```bash
make const
make base
make experimentos
```

Mientras que para ejecutar cualquiera de estos solo basta agregar `run-` antes del parametro. (Ej. `make run-const`)

## Uso

### Construcción los dataset

```bash
make run-const
```

Este comando crea en `./data/` 6 archivos llamados `dataset_i` con $i\in\{10, 11, 12, 13, 14, 25\}$ donde $2^i$ es la cantidad de `unsigned int` presentes en el archivo respectivo

### Escenarios Base

```bash
make run-base
```

Asumiendo que los dataset ya están creados este comando realiza el test de los 4 escenarios base


- Inserción aleatoria, búsqueda uniforme
- Inserción aleatoria, búsqueda sesgada
- Inserción ordenada, búsqueda uniforme
- Inserción ordenada, búsqueda sesgada

Habiendo tomado $c=5$ y $\lambda=\log{\frac{31}{32}}$ se hacen $50*N$ busquedas para cada uno de los arboles creados a partir de los dataset en cada escenario base y luego muestra en la consola los el tiempo que demoró cada creación de arbol en azul y cada ronda de busqueda en verde.

### Experimentos

Asumiendo nuevamente que el dataset de $2^25$ datos ya está creado, este archivo ejecuta los experimentos que comprueban los resultados teóricos de los siguientes teoremas tal como se especifica en la sección 7.3.1 del enunciado tomando $c=3$.

- Sequential Access Theorem
- Working Set Theorem

En el primero de estos se ordenó el dataset ya hecho y se hicieron busquedas en orden de todo el dataset reportando los tiempos cada $\frac{N}{100}$ iteraciones.

Cuidado al ejecutar este archivo ya que durante la sección de _Working Set Theorem_ el experimento en una laptop de 16 GB de ram trabajando en paralelo en ambas estructuras tomó al rededor de 3 horas utilizando cerca de 4 GB de ram durante el proceso.

### Limpieza

```bash
make clean-d
make clean-x
```

Estos archivos vacían las carpetas `./data/` y `./build/` respectivamente, por si es que se quiere ejecutar desde cero la creación de los dataset o compilación

## Miscelaneo

```bash
make say
# o alternativamente
make
```

Muestra en pantalla todo el contenido de `Makefile`