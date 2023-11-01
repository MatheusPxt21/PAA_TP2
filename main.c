#include "Headers/LeituraArquivo.h"

int main(){
    MatrizMapa ptr;
    LeituraMatriz("..\\TP2\\MapasExemplo\\caverna1.txt",&ptr);
    //printf("PASSOU!\n");
    for(int i = 0;i<ptr.LinhasMapa;i++){
        for(int j = 0;j<ptr.ColunasMapa;j++){
            printf(" [%d][%d]=>[%d] ",i,j,ptr.ConteudoMapa[i][j]);
        }
        printf("\n");
    }
    printf("HP: %d\n",ptr.VidaJogador);
    printf("Linha e Coluna Inicial: %d %d \n ",ptr.LinhasInicial,ptr.ColunasInicial);
    printf("Linha e Coluna Final: %d %d \n ",ptr.LinhasFinal,ptr.ColunasFinal);
    return 0;
}