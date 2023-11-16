all:
	gcc main.c Headers/LeituraArquivo.h src/LeituraArquivo.c  Headers/Pilha.h src/Pilha.c Headers/PD_Estudante.h src/PD_Estudante.c 
Linux:
	./a.out
Windows:
	./a.exe