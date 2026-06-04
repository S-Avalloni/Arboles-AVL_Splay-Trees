flags = -fsanitize=undefined,address,leak -fno-omit-frame-pointer -g -Wall -Wextra -std=c11
avl = build/avl.o
splay = build/splay.o


say:
	cat Makefile

build: main $(avl) $(splay)

run-main: build/main
	build/main

main: build/main

build/main: src/main.c $(splay)
	gcc $(flags) $(splay) src/main.c -o build/main

$(avl): include/avl.h include/avl.c
	gcc $(flags) -c include/avl.c -o build/avl.o

$(splay): include/splay.h include/splay.c
	gcc $(flags) -c include/splay.c -o build/splay.o

clean-x:
	rm -f build/*

