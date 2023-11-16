#include "../Headers/MatrizAleatoria.h"


void GerarCavernaAleatoria(MatrizMapa *map)
{
    int contaPocoes = 0;
    int contaMonstros = 0;
    float maxPocoes, maxMonstros;
    int auxAleatorio;
    int auxLinhaInicial, auxLinhaFinal, auxColunaInicial, auxColunaFinal;

    // Gera o número de linhas e colunas aleatoriamente (entre 3 e 8)
    int num_linhas = rand() % 8 + 3;
    int num_colunas = rand() % 8 + 3;

    int areaMatriz = num_linhas * num_colunas;

    maxPocoes = areaMatriz * 0.2;
    maxMonstros = areaMatriz * 0.3;

    printf("Pocoes::: %f\n", maxPocoes);
    printf("Monstros::: %f\n", maxMonstros);

//    auxLinhaInicial = (int)(num_linhas / 2);
//    auxColunaInicial = (int)(num_linhas / 2);
//    auxLinhaFinal = (int)(num_linhas / 2);
//    auxColunaFinal = (int)(num_linhas / 2);

    FILE *arq = fopen("MapasExemplo/CavernaAleatoria.txt", "w");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Escreve informações iniciais
    fprintf(arq, "%d %d %d\n", num_linhas, num_colunas, rand() % 101); // Pontos de vida entre 0 e 100
    map->ConteudoMapa = (int **)malloc(num_linhas * sizeof(int *));
    if (map->ConteudoMapa == NULL) {
        perror("Erro ao alocar memória para ConteudoMapa");
        exit(1);
    }
    
    for(int i = 0; i < num_linhas; i++){
        map->ConteudoMapa[i] = (int *)malloc(num_colunas * sizeof(int));
        for(int j = 0; j < num_colunas; j++){
            auxAleatorio = rand() % 3;
            switch (auxAleatorio)
            {
            case 0:
               // printf("Escolheu 0\n");
                map->ConteudoMapa[i][j] = 0;
                break;
            case 1:
                //printf("Escolheu 1\n");
                if(contaPocoes <= maxPocoes){
                    map->ConteudoMapa[i][j] = rand() % 15 + 1;
                    contaPocoes++;
                }
                else{
                    //printf("mas nao deu -> %d\n", contaPocoes);
                    map->ConteudoMapa[i][j] = 0;
                }
                break;
            case 2:
                //printf("Escolheu 2\n");
                if(contaMonstros <= maxMonstros){
                    map->ConteudoMapa[i][j] = (rand() % 15 + 1) * (-1);
                    contaMonstros++;
                }
                else{
                   //printf("mas nao deu -> %d\n", contaMonstros);
                    map->ConteudoMapa[i][j] = 0;
                }
                break;
            
            default:
                //printf("Escolheu 3\n");
                break;
            }
        }
    }

    // Define a posição de I (Início) na metade direita inferior da matriz
    auxLinhaInicial = rand() % (num_linhas / 2) + (num_linhas / 2);
    auxColunaInicial = rand() % (num_colunas / 2) + (num_colunas / 2);

    // Define a posição de F (Fim) na metade esquerda superior da matriz
    auxLinhaFinal = rand() % (num_linhas / 2);
    auxColunaFinal = rand() % (num_colunas / 2);

    map->ConteudoMapa[auxLinhaFinal][auxColunaFinal] = 'F';
    map->ConteudoMapa[auxLinhaInicial][auxColunaInicial] = 'I';



    for(int i = 0; i < num_linhas; i++){
        for(int j = 0; j <num_colunas; j++){
            printf("[%d] ", map->ConteudoMapa[i][j]);
        }
        printf("\n");
    }



    // Escreve o mapa no arquivo
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            if (i == auxLinhaInicial && j == auxColunaInicial)
            {
                fprintf(arq, "I ");
                continue;
            }
             if (i == auxLinhaFinal && j == auxColunaFinal)
            {
                fprintf(arq, "F ");
                continue;
            }
                fprintf(arq, "%d ", map->ConteudoMapa[i][j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);



    for (int i = 0; i < num_linhas; i++) {
        free(map->ConteudoMapa[i]);
    }
    free(map->ConteudoMapa);

}