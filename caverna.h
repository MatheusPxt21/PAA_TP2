#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

// Estrutura para representar a caverna
typedef struct {

    int linhas;
    int colunas;
    int pontosVida;
    int mapa[MAX_LINHAS][MAX_COLUNAS];

} Caverna;

void lerCaverna(FILE *arquivo, Caverna *caverna);
void imprimirCaminho(FILE *arquivo, int caminho[MAX_LINHAS][MAX_COLUNAS], int i, int j);
void resolverCaverna(Caverna caverna, const char *arquivoSaida);
void imprimirResultadoCaverna(Caverna caverna);