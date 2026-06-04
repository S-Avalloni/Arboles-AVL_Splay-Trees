flags = -fsanitize=undefined,address -g -Wall -Wextra -std=c11
avl = build/avl.o
splay = build/splay.o


say:
	cat Makefile

build: main $(avl) $(splay)

run-main: build/main
	build/main

main: build/main

build/main: src/main.c $(avl) $(splay)
	gcc $(flags) $(avl) $(splay) src/main.c -o build/main

$(avl): include/avl.h include/avl.c
	gcc $(flags) -c include/avl.c -o outputs/avl.o

$(splay): include/avl.h include/avl.c
	gcc $(flags) -c include/avl.c -o outputs/avl.o

clean-v:
	rm -f vectores/*

clean-x:
	rm -f outputs/*