#include "../Headers/Aventureiro.h"

void InicializarAventureiro(MatrizMapa *ptrMapa,Aventureiro *ptrAv){
    //Inicia com os pontos de vida lidos no arquivo
    ptrAv->PontosVidaAtual = ptrMapa->VidaJogador;
    //Inicializa a tabela,armazenará os pontos de vida do jogador durante o percurso
    ptrAv->TabelaPD = (int**)malloc(ptrMapa->LinhasMapa * sizeof(int*));
    for(int i = 0; i < ptrMapa->LinhasMapa; i++){
        ptrAv->TabelaPD[i] = (int*)malloc(ptrMapa->ColunasMapa * sizeof(int));
    }
    //A tabela será inicializado com 0 em todas as posições, apenas a posição inicial será diferente
    // Terá os pontos de vida iniciais

    for(int i = 0;i<ptrMapa->LinhasMapa;i++){
        for(int j = 0;j<ptrMapa->ColunasMapa;j++){
            if(i==ptrMapa->LinhasInicial && j==ptrMapa->ColunasInicial){
                ptrAv->TabelaPD[i][j] = ptrMapa->VidaJogador;
            }else{
                ptrAv->TabelaPD[i][j] = 0;
            }
        }
    }
}

void IniciarDeslocamento(MatrizMapa *ptr,Aventureiro *ptrAv,PilhaCoordenadas *PtrCoordenadas,Fila *Filas){
    InicializarAventureiro(ptr,ptrAv);
    initialize(PtrCoordenadas);
    initializeFila(Filas);
    if(Deslocar(ptr,ptrAv,PtrCoordenadas,Filas)==1){
        EscreverArquivoDeSaida(Filas);
    }else{
        EscreverArquivoDeSaidaErro();
    }
}

int Deslocar(MatrizMapa *ptr, Aventureiro *ptrAv, PilhaCoordenadas *PtrCoordenadas, Fila *Filas){
    //Calcular a primeira Linha
    int controlJ = 1,controlI = 1,i,j,NovoJ = ptr->ColunasInicial,NovoI =ptr->LinhasInicial ;
    for(i =NovoI;controlI == 1;i--){
        ptrAv->TabelaPD[i][NovoJ] = ptrAv->PontosVidaAtual;
        for(j = NovoJ-1;controlJ==1 ;j--){

            controlJ = EsquerdaLivre(i,j,ptrAv,ptr);

        }
        j = EscolherMelhorCaminho(i,ptrAv,ptr);

        controlI = CimaLivre(i,j,ptrAv,ptr);
        NovoJ = j;
        if(i-1>0){
            NovoI = i-1;
            ptrAv->PontosVidaAtual += ptr->ConteudoMapa[NovoI][NovoJ];
        }
        if(ptrAv->PontosVidaAtual<=0){
            break;
        }
        controlJ = 1;
        ApresentarTabelaPD(ptrAv,ptr);
    }
    //Preencher o restante da tabela

    //printf("Depois!\n");

    PreencherFila(ptr,ptrAv,Filas);
    if(ptrAv->TabelaPD[ptr->LinhasFinal][ptr->ColunasFinal]>0){
        return 1;
    }
    return 0;
}

int EsquerdaLivre(int i,int j,Aventureiro *ptrAv,MatrizMapa *ptr){
    //printf("Dentro de Esquerda Livre,posicao i e j: [%d %d]\n",i,j);
    if(j>=0){
        if(i==ptr->LinhasInicial && j==ptr->ColunasInicial){
            ptrAv->TabelaPD[i][j] = ptrAv->PontosVidaAtual;
        }else if(j<ptr->ColunasMapa-1){
            //printf("DENTRO DO ELSE!\n");
            ptrAv->TabelaPD[i][j] = ptrAv->TabelaPD[i][j+1] + ptr->ConteudoMapa[i][j];
        }
        if(ptrAv->TabelaPD[i][j]>0){
            return 1;
        }
    }
    return 0;
}
int CimaLivre(int i,int j,Aventureiro *ptrAv,MatrizMapa *ptr){
    if(i-1>=0){
        ptrAv->TabelaPD[i-1][j] = ptrAv->PontosVidaAtual + ptr->ConteudoMapa[i-1][j];
        if(ptrAv->TabelaPD[i][j]>0){
            return 1;
        }
    }
    return 0;
}
int EscolherMelhorCaminho(int i,Aventureiro *ptrAv,MatrizMapa *ptr){
    int PosicaoMaiorPontoDeVida;
    for(int j = 0;j<ptr->ColunasMapa;j++){
        if(j==0){
            PosicaoMaiorPontoDeVida = j;
        }else{
            if(ptrAv->TabelaPD[i][j]>ptrAv->TabelaPD[i][PosicaoMaiorPontoDeVida]){
                PosicaoMaiorPontoDeVida = j;
            }else if(ptrAv->TabelaPD[i][j]==ptrAv->TabelaPD[i][PosicaoMaiorPontoDeVida]){
                if(i>0){
                    if((ptrAv->TabelaPD[i][j]+ptr->ConteudoMapa[i-1][j]+ptrAv->PontosVidaAtual)>(ptrAv->TabelaPD[i][PosicaoMaiorPontoDeVida] +ptr->ConteudoMapa[i-1][PosicaoMaiorPontoDeVida] + ptrAv->PontosVidaAtual)){
                        PosicaoMaiorPontoDeVida = j;
                    }
                }
            }
        }
    }
    return PosicaoMaiorPontoDeVida;
}
void ApresentarTabelaPD(Aventureiro *ptrAv,MatrizMapa *ptr){
    for(int i = 0;i<ptr->LinhasMapa;i++){
        for(int j = 0;j<ptr->ColunasMapa;j++){
            printf(" [%d] ",ptrAv->TabelaPD[i][j]);
        }
        printf("\n");
    }
}

void PreencherFila(MatrizMapa *ptr,Aventureiro *ptrAv,Fila *fila){
    InserirFila(fila,ptr->LinhasInicial,ptr->ColunasInicial);
    int i = ptr->LinhasInicial,j = ptr->ColunasInicial,flag01,flag02;
    while(1){
        //break;
        if(j-1>=0 && i-1>=0 && ptrAv->TabelaPD[i-1][j]>ptrAv->TabelaPD[i][j-1]){
            //printf("Dentro do primeiro if e antes de IF!\n");
            InserirFila(fila,i-1,j);
            //printf("Depois do primeiro if e antes de IF!\n");
            i += -1;
        }else if(i-1>-0 && j-1>=0 && ptrAv->TabelaPD[i-1][j] < ptrAv->TabelaPD[i][j-1] ){
            InserirFila(fila,i,j-1);
            j += -1;
        }else{
            //Escolher o mais próxima da saída
            //printf("Dentro do else de PF!\n");
            flag01 = i-1;
            flag02 = j-1;
            if(i==0){
                j+=-1;
            }else if(j==0){
                i += -1;
            }else if(j>0 && i>0 &&ptr->LinhasFinal-flag01>ptr->ColunasFinal-flag02){
                j+=-1;
            }else if(j>0 && i>0 &&ptr->LinhasFinal-flag01<ptr->ColunasFinal-flag02){
                i += -1;
            }
            InserirFila(fila,i,j);
        }
        if(i==ptr->LinhasFinal && j==ptr->ColunasFinal){
            break;
        }
        //printf("Valor de I: %d \n",i);
        //printf("Valor de J: %d \n",j);
    }
    //push(ptrCoordenadas,ptr->LinhasFinal,ptr->ColunasFinal);

}

void EscreverArquivoDeSaida(Fila *FILA) {
    FILE *file;
    file = fopen("..\\TP2\\Resultado\\Resultado.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }
    Node* temp = FILA->front;
    while (temp != NULL) {
        fprintf(file, "%d %d\n", temp->linha, temp->coluna);
        temp = temp->next;
    }

    fclose(file);
}
void EscreverArquivoDeSaidaErro(){
    FILE *file;
    file = fopen("..\\TP2\\Resultado\\Resultado.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }
    fprintf(file, "Nao foi possivel sair do labirinto com vida ): RIP\n");
    fclose(file);
}