flags = -fsanitize=undefined,address -g -fno-omit-frame-pointer -Wall -Wextra -std=c11 -O3
avl = build/avl.o
splay = build/splay.o

say:
	cat Makefile

build: main const base $(avl) $(splay)

run-main: build/main
	build/main

run-const: build/const
	build/const

run-base: build/base
	build/base

main: build/main

const: build/const

base: build/base

build/main: src/main.c $(splay) $(avl)
	gcc $(flags) $(splay) $(avl) src/main.c -o build/main

build/const: src/const.c
	gcc $(flags) src/const.c -o build/const

build/base: src/base.c $(splay) $(avl)
	gcc $(flags) $(splay) $(avl) src/base.c -o build/base

$(avl): include/avl.h include/avl.c
	gcc $(flags) -c include/avl.c -o $(avl)

$(splay): include/splay.h include/splay.c
	gcc $(flags) -c include/splay.c -o $(splay)

clean-x:
	rm -f build/*

