#include "caverna.h"


 int pd[MAX_LINHAS][MAX_COLUNAS] = {-1}; // Matriz de programação dinâmica

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
                if (numero[0] == 'F') {
                    // Armazena a posição final
                    caverna->posicaoFinal[0] = i;
                    caverna->posicaoFinal[1] = j;
                    // Armazena no mapa da caverna como caractere
                    caverna->mapa[i][j] = numero[0];
                } else if (numero[0] == 'I') {
                    // Armazena a posição inicial
                    caverna->posicaoInicial[0] = i;
                    caverna->posicaoInicial[1] = j;
                    // Armazena no mapa da caverna como caractere
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
void imprimirCaminho(FILE *arquivo, int i, int j, int x, int y ) {
    if (i == x && j == y) {
       fprintf(arquivo, "%d %d\n", i, j ); 
        return;
    }

    if (i + 1 >= MAX_LINHA ) {
        imprimirCaminho(arquivo, i, j + 1, x, y);
         fprintf(arquivo, "%d %d\n", i, j );
         return;
    } else {
        if (j + 1 >= MAX_COLUNAS)
        {
            imprimirCaminho(arquivo, i + 1, j , x, y);
             fprintf(arquivo, "%d %d\n", i , j);
             return;
        }
        else
        {
            if (pd[i + 1][j] > pd[i][j + 1])
            {
                imprimirCaminho(arquivo, i + 1, j , x, y);
                fprintf(arquivo, "%d %d\n", i , j);
                return;
            }
            else{
                imprimirCaminho(arquivo, i, j + 1, x, y);
                fprintf(arquivo, "%d %d\n", i, j );
                return;
            }
        }
        
    }
    fprintf(arquivo, "%d %d\n", i, j );
}

// Função para resolver a caverna usando programação dinâmica
void resolverCaverna(Caverna caverna, const char *arquivoSaida) {
    
    Fila fila;
    inicializarFila(&fila);

     // Inicializa a primeira célula da matriz de programação dinamica e enfileira a posiçaõ inicial
    pd[caverna.posicaoInicial[0]][caverna.posicaoInicial[1]] = caverna.pontosVida;
    enfileirar(&fila, caverna.posicaoInicial[0], caverna.posicaoInicial[1]);

    //Preenchendo a matriz de programação dinamica
    while ( ! filaVazia(&fila))
    {
        ElementoFila primeiro = fila.frente->elemento;
        desenfileirar(&fila);
        // Tira da fila a posição inicial e a partir dela tenta ir para a esquerda, teste se não é fora da matriz e quantidade de vida que fico  
        if (primeiro.y -1 >= 0 && 
                pd[primeiro.x][primeiro.y - 1] < pd[primeiro.x][primeiro.y] + caverna.mapa[primeiro.x][primeiro.y -1] ) // Checando se posso ir para a esquerda e se preciso trocar o valor da celula da matriz
        {   
            if (primeiro.x != caverna.posicaoFinal[0] || primeiro.y - 1 != caverna.posicaoFinal[1])
            {
                enfileirar(&fila, primeiro.x, primeiro.y - 1);  // enfileira a posição que estamos
            }
            pd[primeiro.x][primeiro.y - 1] = pd[primeiro.x][primeiro.y] + caverna.mapa[primeiro.x][primeiro.y -1];
        }
        //Agora faz a mesma tentiva para a direita
         if (primeiro.x -1 >= 0 && 
                 pd[primeiro.x - 1][primeiro.y] < pd[primeiro.x][primeiro.y] + caverna.mapa[primeiro.x - 1][primeiro.y] ) // Checando se posso ir para cima e se preciso trocar o valor da celula da matriz
        {
            if (primeiro.x - 1 != caverna.posicaoFinal[0] || primeiro.y != caverna.posicaoFinal[1])
            {
                 enfileirar(&fila, primeiro.x - 1, primeiro.y);
            }
            pd[primeiro.x - 1][primeiro.y] = pd[primeiro.x][primeiro.y] + caverna.mapa[primeiro.x - 1][primeiro.y];
        }
    }
    
    // Verifica se é possível sair com vida da caverna
    if (pd[caverna.posicaoFinal[0]][caverna.posicaoFinal[1]] <= 0) {
        // Imprime "impossível" se não for possível
        FILE *saida = fopen(arquivoSaida, "w");
        fprintf(saida, "impossível\n"); 
        fclose(saida);
    } else {
        // Encontra o caminho ótimo e o imprime no arquivo de saída
        FILE *saida = fopen(arquivoSaida, "w");
        imprimirCaminho(saida, caverna.posicaoFinal[0], caverna.posicaoFinal[1], caverna.posicaoInicial[0], caverna.posicaoInicial[1]);
        fclose(saida);
    }
}

void gerar_caverna_aleatoria(const char *arquivo_saida) {
    // Gera o número de linhas e colunas aleatoriamente (entre 3 e 8)
    int num_linhas = rand() % 6 + 3;
    int num_colunas = rand() % 6 + 3;

    FILE *f = fopen(arquivo_saida, "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escreve informações iniciais
    fprintf(f, "%d %d %d\n", num_linhas, num_colunas, rand() % 101); // Pontos de vida entre 0 e 100

    // Gera o mapa aleatório
    srand(time(NULL));

    // Gera a matriz do mapa
    int mapa[num_linhas][num_colunas];
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            int valor = rand() % 41 - 20;  // Números aleatórios entre -20 e 20
            mapa[i][j] = valor;
        }
    }

    // Escolhe posições inicial e final aleatórias
    int posicao_inicial[2] = {rand() % num_linhas, rand() % num_colunas};
    int posicao_final[2] = {rand() % num_linhas, rand() % num_colunas};

    // Garante que as posições inicial e final são diferentes
    while (posicao_inicial[0] == posicao_final[0] && posicao_inicial[1] == posicao_final[1]) {
        posicao_final[0] = rand() % num_linhas;
        posicao_final[1] = rand() % num_colunas;
    }

    // Escreve o mapa no arquivo
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            if (i == posicao_inicial[0] && j == posicao_inicial[1])
            {
                fprintf(f, "I ");
                continue;
            }
             if (i == posicao_final[0] && j == posicao_final[1])
            {
                fprintf(f, "F ");
                continue;
            }
                fprintf(f, "%d ", mapa[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}