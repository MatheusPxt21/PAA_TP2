#include "caverna.h"

// Defina o tamanho máximo para uma linha no arquivo
#define MAX_LINHA 100

// Função para ler os dados de entrada da caverna
void lerCaverna(FILE *arquivo, Caverna *caverna) {
    // Lê o número de linhas, colunas e pontos de vida iniciais
    fscanf(arquivo, "%d %d %d", &caverna->linhas, &caverna->colunas, &caverna->pontosVida);

    // Descarta o restante da linha após a leitura dos valores acima
    fgetc(arquivo);

    // Lê o mapa da caverna
    for (int i = 0; i < caverna->linhas; i++) {
        // Lê uma linha do arquivo
        char linha[MAX_LINHA];
        fgets(linha, sizeof(linha), arquivo);

        // Usa strtok para dividir a linha em tokens
        char *numero = strtok(linha, " ");
        for (int j = 0; j < caverna->colunas; j++) {
            if (numero != NULL) {
                // Verifica se o numero é 'F' ou 'I'
                if (numero[0] == 'F' || numero[0] == 'I') {
                    // Se for 'F' ou 'I', armazene no mapa da caverna como caractere
                    caverna->mapa[i][j] = numero[0];
                } else {
                    // Se não for 'F' ou 'I', leia como um número inteiro
                    sscanf(numero, "%d", &caverna->mapa[i][j]);
                }
                // Obtém o próximo numero
                numero = strtok(NULL, " ");
            }
        }
    }

}


// Função para imprimir o resultado da caverna
void imprimirResultadoCaverna(Caverna caverna) {
    printf("Linhas: %d\n", caverna.linhas);
    printf("Colunas: %d\n", caverna.colunas);
    printf("Pontos de Vida Iniciais: %d\n", caverna.pontosVida);

    printf("Mapa da Caverna:\n");
    for (int i = 0; i < caverna.linhas; i++) {
        for (int j = 0; j < caverna.colunas; j++) {
            if (caverna.mapa[i][j] == 'F' || caverna.mapa[i][j] == 'I') {
                printf("%c ", caverna.mapa[i][j]);
            } else {
                printf("%d ", caverna.mapa[i][j]);
            }
        }
        printf("\n");
    }
}

// Função para imprimir o caminho ótimo no arquivo de saída
void imprimirCaminho(FILE *arquivo, int caminho[MAX_LINHAS][MAX_COLUNAS], int i, int j) {
    if (i == 0 && j == 0) {
        return;
    }

    fprintf(arquivo, "%d %d\n", i, j);

    if (caminho[i][j] == 1) {
        imprimirCaminho(arquivo, caminho, i - 1, j);
    } else {
        imprimirCaminho(arquivo, caminho, i, j - 1);
    }
}

//Função para resolver a caverna usando programação dinâmica
void resolverCaverna(Caverna caverna, const char *arquivoSaida) {
    int dp[MAX_LINHAS][MAX_COLUNAS] = {0}; // Matriz de programação dinâmica
    int caminho[MAX_LINHAS][MAX_COLUNAS] = {0}; // Matriz para rastreamento do caminho

    // Inicializa a primeira célula da matriz dp
    dp[0][0] = caverna.mapa[0][0];

    // Preenche a primeira coluna da matriz dp
    for (int i = 1; i < caverna.linhas; i++) {
        dp[i][0] = dp[i - 1][0] + caverna.mapa[i][0];
        caminho[i][0] = 1; // 1 indica que veio de cima
    }

    // Preenche a primeira linha da matriz dp
    for (int j = 1; j < caverna.colunas; j++) {
        dp[0][j] = dp[0][j - 1] + caverna.mapa[0][j];
        caminho[0][j] = 2; // 2 indica que veio da esquerda
    }

    // Preenche o restante da matriz dp
    for (int i = 1; i < caverna.linhas; i++) {
        for (int j = 1; j < caverna.colunas; j++) {
            int esquerda = dp[i][j - 1];
            int cima = dp[i - 1][j];

            if (esquerda > cima) {
                dp[i][j] = esquerda + caverna.mapa[i][j];
                caminho[i][j] = 2; // 2 indica que veio da esquerda
            } else {
                dp[i][j] = cima + caverna.mapa[i][j];
                caminho[i][j] = 1; // 1 indica que veio de cima
            }
        }
    }

    // Verifica se é possível sair com vida da caverna
    if (dp[caverna.linhas - 1][caverna.colunas - 1] <= 0) {
        // Imprime "impossível" se não for possível
        FILE *saida = fopen(arquivoSaida, "w");
        fprintf(saida, "impossível\n");
        fclose(saida);
    } else {
        // Encontra o caminho ótimo e o imprime no arquivo de saída
        FILE *saida = fopen(arquivoSaida, "w");
        imprimirCaminho(saida, caminho, caverna.linhas - 1, caverna.colunas - 1);
        fclose(saida);
    }
}
