#include "Headers/Aventureiro.h"

int main(){
    MatrizMapa ptr;
    LeituraMatriz("..\\TP2\\MapasExemplo\\caverna1.txt",&ptr);
    PilhaCoordenadas PtrCoordenadas;
    FilaPilhas filas;
    Aventureiro ptrAv;
    //printf("PASSOU!\n");
    for(int i = 0;i<ptr.LinhasMapa;i++){
        for(int j = 0;j<ptr.ColunasMapa;j++){
            //printf(" [%d][%d]=>[%d] ",i,j,ptr.ConteudoMapa[i][j]);
        }
        //printf("\n");
    }
    //printf("HP: %d\n",ptr.VidaJogador);
    //printf("Linha e Coluna Inicial: %d %d \n ",ptr.LinhasInicial,ptr.ColunasInicial);
    //printf("Linha e Coluna Final: %d %d \n ",ptr.LinhasFinal,ptr.ColunasFinal);
    IniciarDeslocamento(&ptr,&ptrAv,&PtrCoordenadas,&filas);
    //ApresentarTabelaSimplex(&ptrAv,&ptr);

    return 0;
}