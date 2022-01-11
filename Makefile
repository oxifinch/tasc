run: tasc
	./tasc testing/file1.c

tasc: build/main.o
	gcc -Wall build/main.o -o tasc

build/main.o: src/main.c
	ctags -R src/main.c
	gcc -c src/main.c -o build/main.o

install: tasc
	cp tasc ~/.local/bin/
