#include "../Headers/LeituraArquivo.h"

void LeituraMatriz(const char *arqEntrada,MatrizMapa *ptr){
    char celula[20];
    int conteudo,linha,coluna,vida;
    FILE *file = fopen(arqEntrada, "r");
    if(file == NULL){
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fscanf(file, "%d %d %d",&linha,&coluna,&vida);
    ptr->LinhasMapa = linha;
    ptr->ColunasMapa = coluna;
    ptr->VidaJogador = vida;
    ptr->ConteudoMapa = (int**)malloc(ptr->LinhasMapa * sizeof(int*));
    if (ptr->ConteudoMapa == NULL) {
        perror("Erro ao alocar memória para ConteudoMapa");
        exit(1);
    }
    for(int i = 0; i < ptr->LinhasMapa; i++){
        ptr->ConteudoMapa[i] = (int*)malloc(ptr->ColunasMapa * sizeof(int));
    }
    for(int i = 0; i< ptr->LinhasMapa; i++){
        for(int j = 0; j<ptr->ColunasMapa; j++){

            do{
                fscanf(file, "%s", celula);
                if(!strcmp(celula,"I") || !strcmp(celula,"F")){
                    if(!strcmp(celula,"I")){
                        ptr->LinhasInicial = i;
                        ptr->ColunasInicial = j;
                    }
                    if(!strcmp(celula,"F")){
                        ptr->LinhasFinal = i;
                        ptr->ColunasFinal = j;
                    }
                    strcpy(celula,"0");
                }
                conteudo = atoi(celula);
            }while(!strcmp(celula," ") || !strcmp(celula,"\n"));

            ptr->ConteudoMapa[i][j] = conteudo;
            setbuf(stdin, NULL);
        }
    }
    fclose(file);
}

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
    /*
    // Preenche a matriz com valores aleatórios
    for (int i = 0; i < num_linhas; i++) {
        map->ConteudoMapa[i] = (int *)malloc(num_colunas * sizeof(int));
        for (int j = 0; j < num_colunas; j++) {
            // Prioriza o valor zero
            if (rand() % 3 == 0) {
                map->ConteudoMapa[i][j] = 0;
            } else {
                // Gera valores positivos ou negativos aleatoriamente
                map->ConteudoMapa[i][j] = (rand() % 2 == 0 ? 1 : -1) * (rand() % 10 + 1);
            }
        }
    }

    // Define a posição de I (Início) e F (Fim)
    map->LinhasInicial = rand() % (num_linhas / 2); // Na metade direita da matriz
    map->ColunasInicial = rand() % num_colunas;

    map->LinhasFinal = map->LinhasInicial + rand() % (num_linhas / 2) + 1; // Acima de I e na metade esquerda
    map->ColunasFinal = rand() % (num_colunas / 2);
    */
    
}