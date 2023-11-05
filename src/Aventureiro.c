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

void IniciarDeslocamento(MatrizMapa *ptr,Aventureiro *ptrAv,PilhaCoordenadas *PtrCoordenadas,PilhaRamificado *PtrRamificado,FilaPilhas *Filas){

    int i,j,LinhaRamificacao,ColunaRamificacao;
    i = ptr->LinhasInicial;
    j = ptr->ColunasInicial;
    InicializarAventureiro(ptr,ptrAv);
    initialize(PtrCoordenadas);
    inicializarRamificacao(PtrRamificado);
    initializeFilaPilhas(Filas);
    Deslocar(ptr,ptrAv,&i,&j,&LinhaRamificacao,&ColunaRamificacao,PtrCoordenadas,PtrRamificado,Filas);

}

int Deslocar(MatrizMapa *ptr, Aventureiro *ptrAv, int *i, int *j, int *LinhaRamificacao, int *ColunaRamificacao, PilhaCoordenadas *PtrCoordenadas, PilhaRamificado *PtrRamificado, FilaPilhas *Filas){
    //Ideia geral:
    // Semelhante ao TP anterior envolvendo o backtracking, a função irá explorar as ramificações, nesse caso esquerda e cima
    //A tabela será acrescida com os valores dos pontos de vida do jogador ao longo do trajeto pelo mapa
    //Quando uma ramificação for totalmente testada, o mapa é restaurado até aquela posição.

    if(ptrAv->PontosVidaAtual>0){
        //Colocar a função de restaurar vida
    }
    //Caso a saida for encontrada e o jogador ainda estiver com vida
    if(ptrAv->PontosVidaAtual>0 && *i == ptr->LinhasFinal && *j==ptr->ColunasFinal){
        push(PtrCoordenadas,*i,*j,ptrAv->PontosVidaAtual);
        InserirFilaPilhas(Filas,PtrCoordenadas,ptrAv->PontosVidaAtual);
    }else if(ptrAv->PontosVidaAtual<=0){

    }

    if(EsquerdaLivre(*j) && CimaLivre(*i)){
        *LinhaRamificacao = *i;
        *ColunaRamificacao = *j;
        push(PtrCoordenadas,*i,*j,ptrAv->PontosVidaAtual);
        pushRamificacao(PtrRamificado,*i,*j,ptrAv->PontosVidaAtual);
        if(EsquerdaLivre(*j) && PtrRamificado->topo->Esquerda==-1){
            PtrRamificado->topo->Esquerda = 1;
            (*j) = (*j) + 1;
            ptrAv->TabelaPD[*i][*j] = ptrAv->PontosVidaAtual + ptr->ConteudoMapa[*i][*j];
            Deslocar(ptr,ptrAv,i,j,LinhaRamificacao,ColunaRamificacao,PtrCoordenadas,PtrRamificado,Filas);

            //Função LimparMatriz e restaurar pontos de vida, voltar até o estado em que a ramificação foi feita.

        }else{
            PtrRamificado->topo->Esquerda = 0;
        }
        if(CimaLivre(*j) && PtrRamificado->topo->Cima==-1){
            PtrRamificado->topo->Cima = 1;
            (*i) = (*i) + 1;
            ptrAv->TabelaPD[*i][*j] = ptrAv->PontosVidaAtual + ptr->ConteudoMapa[*i][*j];
            Deslocar(ptr,ptrAv,i,j,LinhaRamificacao,ColunaRamificacao,PtrCoordenadas,PtrRamificado,Filas);

            //Função LimparMatriz e restaurar pontos de vida, voltar até o estado em que a ramificação foi feita.

        }else{
            PtrRamificado->topo->Cima = 0;
        }

        //Limpar a tabela já que a ramificação foi testada, retirar da pilha e restaurar os pontos de vida no ponto da última ramificação.
        Deslocar(ptr,ptrAv,i,j,LinhaRamificacao,ColunaRamificacao,PtrCoordenadas,PtrRamificado,Filas);


    }else{
        //Apenas um caminho válido
        if(EsquerdaLivre(*j)){
            (*j) = (*j) + 1;
            ptrAv->TabelaPD[*i][*j] = ptrAv->PontosVidaAtual + ptr->ConteudoMapa[*i][*j];
            Deslocar(ptr,ptrAv,i,j,LinhaRamificacao,ColunaRamificacao,PtrCoordenadas,PtrRamificado,Filas);
        }
        if(CimaLivre(*i)){
            (*i) = (*i) + 1;
            ptrAv->TabelaPD[*i][*j] = ptrAv->PontosVidaAtual + ptr->ConteudoMapa[*i][*j];
            Deslocar(ptr,ptrAv,i,j,LinhaRamificacao,ColunaRamificacao,PtrCoordenadas,PtrRamificado,Filas);

        }
    }

    return 0;
}

int EsquerdaLivre(int j){
    if(j>0){
        return 1;
    }else{
        return 0;
    }

}
int CimaLivre(int i){
    if(i>0){
        return 1;
    }else{
        return 0;
    }
}