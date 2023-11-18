#include "Headers/Aventureiro.h"

#define TAMANHO_CAMINHO_ARQUIVO 100

int main(int argc, char *argv[]) {
    // Verifica se foi fornecido o nome do arquivo como argumento
    if (argc != 2) {
        printf("Uso: %s <arquivo.txt>\n", argv[0]);
        return 1; // Encerra o programa com código de erro
    }

    srand(time(NULL));

    MatrizMapa map;
    Aventureiro avent;
    PilhaCoordenadas ptrCoordenadas;
    Fila ptrFila;

    // Concatena o caminho base com o nome do arquivo fornecido como argumento
    char caminhoArquivo[TAMANHO_CAMINHO_ARQUIVO];
    snprintf(caminhoArquivo, TAMANHO_CAMINHO_ARQUIVO, "MapasExemplo/%s", argv[1]);

    LeituraMatriz(caminhoArquivo, &map);

    IniciarDeslocamento(&map, &avent, &ptrCoordenadas, &ptrFila);

    return 0;

}