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

    ptrEs->Caminho = (int*)malloc(sizeof(int));
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
        //printf("Olhando a posicao map->ConteudoMapa[%d][%d]\n", linhaAtual, colunaAtual);
        
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

   // FazerCaminho(est, map);

   // Imprime(est);
}

void ApresentarTabelaPD(Estudante *ptrAv,MatrizMapa *ptr){
    for(int i = 0;i<ptr->LinhasMapa;i++){
        for(int j = 0;j<ptr->ColunasMapa;j++){
            printf(" [%d] ",ptrAv->TabelaPD[i][j]);
        }
        printf("\n");
    }
}

void FazerCaminho(Estudante *est, MatrizMapa *map)
{
    int linhaAtual = map->LinhaFinal;
    int colunaAtual = map->ColunaFinal;

    printf("\nLinhaFinal: %d\n", linhaAtual);
    printf("ColunaFinal: %d\n", colunaAtual);
    

    int tamanhoCaminho = 0;
    int capacidadeCaminho = 10; // Um valor inicial arbitrário
    est->Caminho = (int *)malloc(capacidadeCaminho * sizeof(int));

    est->Caminho[tamanhoCaminho++] = linhaAtual;
    est->Caminho[tamanhoCaminho++] = colunaAtual;

    do{
        /**
         * Verifica se o valor à direita é maior do que o valor abaixo
         */
        if(est->TabelaPD[linhaAtual +1][colunaAtual] > est->TabelaPD[linhaAtual][colunaAtual +1]){
            linhaAtual++;
            est->Caminho[tamanhoCaminho++] = linhaAtual;
            est->Caminho[tamanhoCaminho++] = colunaAtual;
        }else{
            colunaAtual++;
            est->Caminho[tamanhoCaminho++] = linhaAtual;
            est->Caminho[tamanhoCaminho++] = colunaAtual;
        }

    }while(linhaAtual != map->LinhaInicial && colunaAtual != map->ColunaInicial);

    if(est->TabelaPD[linhaAtual +1][colunaAtual] > est->TabelaPD[linhaAtual][colunaAtual +1]){
        linhaAtual++;
        est->Caminho[tamanhoCaminho++] = linhaAtual;
        est->Caminho[tamanhoCaminho++] = colunaAtual;
    }else{
        colunaAtual++;
        est->Caminho[tamanhoCaminho++] = linhaAtual;
        est->Caminho[tamanhoCaminho++] = colunaAtual;
    }

    //est->Caminho = (int *)realloc(est->Caminho, tamanhoCaminho * sizeof(int));

}

void EscreverArquivoDeSaidaErro()
{

}

void Imprime(Estudante *est){
    int tamanhoCaminho = sizeof(est->Caminho) * 2; // O dobro do tamanho, pois armazenamos linhas e colunas alternadamente

    printf("Caminho: ");
    for (int i = 0; i < tamanhoCaminho; i += 2) {
        printf("(%d, %d) ", est->Caminho[i], est->Caminho[i + 1]);
    }
    printf("\n");
}