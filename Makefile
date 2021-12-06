run: tasc
	./tasc

tasc: build/main.o
	gcc build/main.o -o tasc

build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o
