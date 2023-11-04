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

    InicializarAventureiro(ptr,ptrAv);
    initialize(PtrCoordenadas);
    inicializarRamificacao(PtrRamificado);
    initializeFilaPilhas(Filas);
    Deslocar(ptr,ptrAv,PtrCoordenadas,PtrRamificado,Filas);

}

int Deslocar(MatrizMapa *ptr,Aventureiro *ptrAv,PilhaCoordenadas *PtrCoordenadas,PilhaRamificado *PtrRamificado,FilaPilhas *Filas){
    //Ideia geral:
    // Semelhante ao TP anterior envolvendo o backtracking, a função irá explorar as ramificações, nesse caso esquerda e cima
    //A tabela será acrescida com os valores dos pontos de vida do jogador ao longo do trajeto pelo mapa
    //Quando uma ramificação for totalmente testada, o mapa é restaurado até aquela posição.
    int i = ptr->LinhasInicial;
    int j = ptr->ColunasInicial;
    int control = 0;
    int Esquerda = 0,Cima = 0;
    //Ideia inicial fazer sem recursão
    do{
        if(ptrAv->PontosVidaAtual==0){
            //Caso em que o jogador tenha os pontos de vida zerados
        }
        if(i==ptr->LinhasFinal && j==ptr->ColunasFinal && ptrAv->PontosVidaAtual>0){
            //Foi encontrado um caminho válido até a saída, armazenar na fila de pilhas.
            push(PtrCoordenadas,i,j,ptrAv->PontosVidaAtual);
            InserirFilaPilhas(Filas,PtrCoordenadas,ptrAv->PontosVidaAtual);

        }
        //Nesse contexto com o mapa, não há obstáculos, os únicos pontos que não haverá ramificação será quando o jogador estiver na
        // linha 0(impossível subir) e na coluna 0(impossível andar para esquerda
        if(i>0 && j>0){
            pushRamificacao(PtrRamificado,i,j,ptrAv->PontosVidaAtual);
            push(PtrCoordenadas,i,j,ptrAv->PontosVidaAtual);
            if(EsquerdaLivre(j) && PtrRamificado->topo->Esquerda==-1){
                PtrRamificado->topo->Esquerda = 1;
                j = j + 1;
                control = 1;
            }
            if(control == 0 && CimaLivre(j) && PtrRamificado->topo->Cima==-1){
                PtrRamificado->topo->Cima = 1;
                i = i + 1;
            }

            if(PtrRamificado->topo->Cima!=-1 && PtrRamificado->topo->Esquerda!=-1){
                popRamificacao(PtrRamificado);
                //Adicionar Limpar Matriz
            }

        }else if(EsquerdaLivre(j) || CimaLivre(i)){
            //Caso em que não há ramificação apenas esquerda ou cima são direções válidas
            push(PtrCoordenadas,i,j,ptrAv->PontosVidaAtual);
            if(EsquerdaLivre(j) && CimaLivre(i)!=1){
                Cima = 0;
                Esquerda = 1;
            }else if(EsquerdaLivre(j)!=1 && CimaLivre(i)){
                Esquerda = 0;
                Cima = 1;
            }
            if(Esquerda){
                j = j + 1;
            }else if(Cima){
                i = i + 1;
            }
            Esquerda = 0;
            Cima = 0;
        }else{
            //Caso não tenha mais caminho.
        }
        ptrAv->PontosVidaAtual += ptr->ConteudoMapa[i][j];
        ptrAv->TabelaPD[i][j] = ptrAv->PontosVidaAtual;
        control = 0;

        if(estaVazioRamificacao(PtrRamificado) && isEmptyFilaPilhas(Filas)!=1){
            //Significa que um caminho foi encontrado e não tem mais ramificações a serem testadas.
            return 1;
        }
    } while (estaVazioRamificacao(PtrRamificado)!=1);
    //Nenhuma saída encontrada, imprimir impossível no arquivo de saída.
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