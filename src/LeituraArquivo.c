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
                        ptr->LinhaInicial = i;
                        ptr->ColunaInicial = j;
                    }
                    if(!strcmp(celula,"F")){
                        ptr->LinhaFinal = i;
                        ptr->ColunaFinal = j;
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