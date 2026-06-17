flags = -fsanitize=undefined,address -g -fno-omit-frame-pointer -Wall -Wextra -std=c11 -O3
avl = build/avl.o
splay = build/splay.o
trees = build/trees.o

say:
	cat Makefile

build: $(avl) $(splay) $(trees) const base experimentos 

run-const: build/const
	build/const

run-base: build/base
	build/base

run-experimentos: build/experimentos
	build/experimentos

const: build/const

base: build/base

experimentos: build/experimentos

build/const: src/const.c
	gcc $(flags) src/const.c -o build/const

build/base: src/base.c $(trees)
	gcc $(flags) $(trees) $(avl) $(splay) src/base.c -o build/base

build/experimentos: src/experimentos.c $(trees)
	gcc $(flags) $(trees) $(avl) $(splay) src/experimentos.c -o build/experimentos

$(avl): include/avl.h include/avl.c
	gcc $(flags) -c include/avl.c -o $(avl)

$(splay): include/splay.h include/splay.c
	gcc $(flags) -c include/splay.c -o $(splay)

$(trees): include/trees.h include/trees.c $(avl) $(splay)
	gcc $(flags) -c include/trees.c -o $(trees)

clean-d:
	rm -f data/*

clean-x:
	rm -f build/*

