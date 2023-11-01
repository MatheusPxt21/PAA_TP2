#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MatrizMapa{
    int ColunasMapa,LinhasMapa;
    int ColunasInicial,LinhasInicial,ColunasFinal,LinhasFinal;
    int VidaJogador;
    int **ConteudoMapa;
}MatrizMapa;

void LeituraMatriz(const char *arqEntrada,MatrizMapa *ptr);
