tasc: build/main.o
	gcc -Wall build/main.o -o tasc

test: tasc
	./tasc testing/file1.c

install: tasc
	cp tasc ~/.local/bin/
	
build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o
