run: tasc
	./tasc src/main.c

tasc: build/main.o build/files.o build/parsing.o
	ctags -R src/*
	gcc build/main.o build/files.o build/parsing.o -o tasc

build/main.o: src/main.c
	gcc -Wall -c src/main.c -o build/main.o

build/files.o: src/files.c
	gcc -Wall -c src/files.c -o build/files.o

build/parsing.o: src/parsing.c
	gcc -Wall -c src/parsing.c -o build/parsing.o

debug: src/main.c src/files.c src/parsing.c
	gcc -g src/main.c src/files.c src/parsing.c -o debug
	gdb --args ./debug src/main.c

