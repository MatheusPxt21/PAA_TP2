all: main

main: main.c Headers/MatrizAleatoria.h src/MatrizAleatoria.c
	gcc main.c src/MatrizAleatoria.c -o randon

Linux:
	./randon

Windows:
	./randon.exe

clean:
	rm -f randon