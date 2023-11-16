#include "../Headers/PD_Estudante.h"

void InicializarEstudante(MatrizMapa *ptrMapa, Estudante *ptrEs)
{
    //Inicia com os pontos de vida lidos no arquivo
    ptrEs->PontosVidaAtual = ptrMapa->VidaJogador;

    //Inicializa a tabela,armazenará os pontos de vida do jogador durante o percurso
    ptrEs->TabelaPD = (int**)malloc(ptrMapa->LinhasMapa * sizeof(int*));
    for(int i = 0; i < ptrMapa->LinhasMapa; i++){
        ptrEs->TabelaPD[i] = (int*)malloc(ptrMapa->ColunasMapa * sizeof(int));
    }

    /*
    * A tabela será inicializada com zero para todas as posições, exceto a inicial, inicializada
    * com a vida inicial do estudante
    */
    for(int i = 0; i < ptrMapa->LinhasMapa; i++){
        for(int j = 0; j < ptrMapa->ColunasMapa; j++){
            if(i == ptrMapa->LinhaInicial && j == ptrMapa->ColunaInicial){
                ptrEs->TabelaPD[i][j] = ptrMapa->VidaJogador;
            }else{
                ptrEs->TabelaPD[i][j] = 0;
            }
        }
    }
}

void Deslocar(MatrizMapa *map, Estudante *est)
{
    
    InicializarEstudante(map, est);

    int linhaAtual = map->LinhaInicial;
    int colunaAtual = map->ColunaInicial;


    /**
     *  Insere o valor da vida na posição da tabela PD correspondente à posição tida como inicial
     *  Isso fica fora do do-while para que a posição de análise atual não seja computada duas vezes
     */
    est->TabelaPD[linhaAtual][colunaAtual] = est->PontosVidaAtual + map->ConteudoMapa[linhaAtual][colunaAtual];

    
    do{ 
        printf("Olhando a posicao map->ConteudoMapa[%d][%d]\n", linhaAtual, colunaAtual);
        //Preenchendo a posição à esquerda da posição atual:
        est->TabelaPD[linhaAtual][colunaAtual -1] = est->PontosVidaAtual + map->ConteudoMapa[linhaAtual][colunaAtual -1];
    
        //Preenchendo a posição acima da posição atual:
        est->TabelaPD[linhaAtual -1][colunaAtual] = est->PontosVidaAtual + map->ConteudoMapa[linhaAtual -1][colunaAtual];

        /*
        *  Verifica se o valor armazenado acima é maior do que o valor armazenado à esquerda,
        * ou seja, se acima ele terá uma pontuação de vida maior do que na esquerda
        */
        if(est->TabelaPD[linhaAtual -1][colunaAtual] > est->TabelaPD[linhaAtual][colunaAtual - 1]){
            /*
            *  Caso o valor acima seja maior, a linha atual é decrementada em uma unidade.
            * Desse modo, o algoritmo terá que a posição atual passará a ser "uma casa" acima
            * da posição que estava até então
            */
           linhaAtual--;
        }else{
            /*
            * Nesse caso percebeu que à esquerda teria uma vida maior.
            * Com isso, a coluna atual será decrementada em uma unidade
            */
           colunaAtual--;
        }

        est->PontosVidaAtual = est->TabelaPD[linhaAtual][colunaAtual];

    }while(linhaAtual != map->LinhaFinal && colunaAtual != map->ColunaFinal);
    
    //Preenchendo a posição à esquerda da posição atual:
    est->TabelaPD[linhaAtual][colunaAtual -1] = est->PontosVidaAtual + map->ConteudoMapa[linhaAtual][colunaAtual -1];

    //Preenchendo a posição acima da posição atual:
    est->TabelaPD[linhaAtual -1][colunaAtual] = est->PontosVidaAtual + map->ConteudoMapa[linhaAtual -1][colunaAtual];



    ApresentarTabelaPD(est, map);
}

void ApresentarTabelaPD(Estudante *ptrAv,MatrizMapa *ptr){
    for(int i = 0;i<ptr->LinhasMapa;i++){
        for(int j = 0;j<ptr->ColunasMapa;j++){
            printf(" [%d] ",ptrAv->TabelaPD[i][j]);
        }
        printf("\n");
    }
}

//void IniciarDeslocamento(MatrizMapa *ptr,Estudante *ptrEs,PilhaCoordenadas *PtrCoordenadas,Fila *Filas);

//int Deslocar(MatrizMapa *ptr, Estudante *ptrEs, PilhaCoordenadas *PtrCoordenadas, Fila *Filas);
/*
int EsquerdaLivre(int i,int j,Estudante *ptrEs,MatrizMapa *ptr)
{

}

int CimaLivre(int i,int j,Estudante *ptrEs,MatrizMapa *ptr)
{

}

int EscolherMelhorCaminho(int i,Estudante *ptrEs,MatrizMapa *ptr)
{

}

void ApresentarTabelaPD(Estudante *ptrEs,MatrizMapa *ptr)
{

}

//void PreencherFila(MatrizMapa *ptr,Estudante *ptrEs,Fila *fila);

//void EscreverArquivoDeSaida(Fila *fila);

void EscreverArquivoDeSaidaErro()
{

}
*/