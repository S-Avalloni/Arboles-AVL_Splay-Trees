flags = -fsanitize=undefined,leak -fno-omit-frame-pointer -g -Wall -Wextra -std=c11
avl = build/avl.o
splay = build/splay.o


say:
	cat Makefile

build: main $(avl) $(splay)

run-main: build/main
	build/main

run-const: build/const
	build/const

main: build/main

const: build/const

build/main: src/main.c $(splay) $(avl)
	gcc $(flags) $(splay) $(avl) src/main.c -o build/main

build/const: src/const.c $(splay)
	gcc $(flags) $(splay) $(avl) src/const.c -o build/const

$(avl): include/avl.h include/avl.c
	gcc $(flags) -c include/avl.c -o build/avl.o

$(splay): include/splay.h include/splay.c
	gcc $(flags) -c include/splay.c -o build/splay.o

clean-x:
	rm -f build/*

