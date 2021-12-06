run: tasc
	./tasc

tasc: build/main.o build/files.o
	gcc build/main.o build/files.o -o tasc

build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o

build/files.o: src/files.c
	gcc -c src/files.c -o build/files.o
