all: main

main: main.c Headers/MatrizAleatoria.h src/MatrizAleatoria.c
	gcc main.c src/MatrizAleatoria.c -o random

Linux:
	./random

Windows:
	./random.exe

clean:
	rm -f random