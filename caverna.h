#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"fila.h"

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

// Estrutura para representar a caverna
typedef struct {

    int linhas;
    int colunas;
    int pontosVida;
    int mapa[MAX_LINHAS][MAX_COLUNAS];
    int posicaoFinal[2];
    int posicaoInicial[2];

} Caverna;

// Protótipos de funções
void lerCaverna(FILE *arquivo, Caverna *caverna);
void imprimirCaminho(FILE *arquivo, int i, int j, int x, int y );
void resolverCaverna(Caverna caverna, const char *arquivoSaida);
void imprimirResultadoCaverna(Caverna caverna);
void gerar_caverna_aleatoria(const char *arquivo_saida);