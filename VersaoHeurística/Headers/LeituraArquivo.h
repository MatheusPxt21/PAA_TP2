#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct MatrizMapa{
    int ColunasMapa,LinhasMapa;
    int ColunaInicial, LinhaInicial, ColunaFinal, LinhaFinal;
    int VidaJogador;
    int **ConteudoMapa;
}MatrizMapa;

void LeituraMatriz(const char *arqEntrada,MatrizMapa *ptr);

void ImprimeArquivoLido(MatrizMapa *ptr);
