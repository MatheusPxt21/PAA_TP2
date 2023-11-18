all: main

main: main.c Headers/LeituraArquivo.h src/LeituraArquivo.c Headers/PD_Estudante.h src/PD_Estudante.c Headers/Pilha.h src/Pilha.c
	gcc main.c src/LeituraArquivo.c src/Pilha.c src/PD_Estudante.c -o main

Linux:
	./main

Windows:
	./main.exe

clean:
	rm -f main