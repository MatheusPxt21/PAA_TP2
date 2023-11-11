#include "caverna.h"


int main() {
    FILE *entrada = fopen("caverna3.txt", "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo de entrada.");
        return 1;
    }

    Caverna caverna;
    lerCaverna(entrada, &caverna);
    fclose(entrada);
    //imprimirResultadoCaverna(caverna);
    resolverCaverna(caverna, "resultado2.txt");

    //gerar_caverna_aleatoria("caverna_aleatoria.txt");

    return 0;
}
