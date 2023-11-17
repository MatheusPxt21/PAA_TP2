#include "caverna.h"

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos é correto
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo.txt>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada fornecido pela linha de comando
    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo de entrada.");
        return 1;
    }

    Caverna caverna;
    lerCaverna(entrada, &caverna);
    fclose(entrada);

    // Chama a função para resolver a caverna e especifica o nome do arquivo de saída
    resolverCaverna(caverna, "resultado.txt");

    // Gera uma caverna aleatória com nome "caverna_aleatoria.txt"
    gerar_caverna_aleatoria("caverna_aleatoria.txt");

    return 0;
}

