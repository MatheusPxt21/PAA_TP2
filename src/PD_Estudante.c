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
    int LinhaORColuna, AUXL,AUXC,LinhaAUX,ColunaAux,UltimaColuna,UltimaLinha;

    /**
     *  Insere o valor da vida na posição da tabela PD correspondente à posição tida como inicial
     *  Isso fica fora do do-while para que a posição de análise atual não seja computada duas vezes
     */
    est->TabelaPD[linhaAtual][colunaAtual] = est->PontosVidaAtual + map->ConteudoMapa[linhaAtual][colunaAtual];

    //printf("\nPontos de vida: %d\n", map->VidaJogador);

    do{         
        //Preenchendo a posição à esquerda da posição atual:
        if(map->LinhaFinal ==linhaAtual && map->ColunaFinal==colunaAtual){
            break;
        }
        if(linhaAtual==0 && colunaAtual==0){
            break;
        }
        if(linhaAtual==0 || colunaAtual==0){
            if(linhaAtual==0){
                est->TabelaPD[linhaAtual][colunaAtual -1] += est->PontosVidaAtual + map->ConteudoMapa[linhaAtual][colunaAtual-1];
                colunaAtual-=1;
            }else if(colunaAtual==0){
                est->TabelaPD[linhaAtual -1][colunaAtual] += est->PontosVidaAtual + map->ConteudoMapa[linhaAtual-1][colunaAtual];
                linhaAtual-=1;
            }
            ApresentarTabelaPD(est, map);

        }else{
            est->TabelaPD[linhaAtual][colunaAtual -1] += est->PontosVidaAtual + map->ConteudoMapa[linhaAtual][colunaAtual -1];
    
            //Preenchendo a posição acima da posição atual:
            est->TabelaPD[linhaAtual -1][colunaAtual] += est->PontosVidaAtual + map->ConteudoMapa[linhaAtual -1][colunaAtual];

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
            }else if(est->TabelaPD[linhaAtual -1][colunaAtual] < est->TabelaPD[linhaAtual][colunaAtual - 1]){
            /*
            * Nesse caso percebeu que à esquerda teria uma vida maior.
            * Com isso, a coluna atual será decrementada em uma unidade
            */
           colunaAtual--;
            }else{
            AUXL = 0,AUXC = 0;
            //printf("AUXL ==> %d \n AUXC ==> %d\n",AUXL,AUXC);
            LinhaAUX = linhaAtual;
            ColunaAux = colunaAtual;
            //printf("LINHA AUX: %d Coluna Aux: %d\n",LinhaAUX,ColunaAux);
            while(LinhaAUX>0 || ColunaAux>0 && AUXC==AUXL){
                if(AUXL==0 && AUXC==0){
                    AUXL = map->ConteudoMapa[LinhaAUX][ColunaAux];
                    AUXC =  map->ConteudoMapa[LinhaAUX][ColunaAux];
                }
                if(LinhaAUX>0&&ColunaAux==0){
                    //printf("Entrou Aqui,segundo IF!\n");
                    AUXL += map->ConteudoMapa[LinhaAUX -1][UltimaColuna];
                    AUXC +=  map->ConteudoMapa[LinhaAUX-1][ColunaAux];
                    //printf("AUXL ==> %d \n AUXC ==> %d\n",AUXL,AUXC);
                    LinhaAUX -=1;
                }else if(ColunaAux>0 && LinhaAUX==0){
                    AUXL += map->ConteudoMapa[LinhaAUX][ColunaAux-1];
                    AUXC +=  map->ConteudoMapa[UltimaLinha][ColunaAux-1];
                    ColunaAux -=1;
                }else{
                    AUXL += map->ConteudoMapa[LinhaAUX -1][ColunaAux];
                    UltimaColuna = ColunaAux;
                    AUXC+=map->ConteudoMapa[LinhaAUX][ColunaAux-1];
                    UltimaLinha = LinhaAUX;
                    //printf("Linha -1 Mapa:[%d %d] %d \n",LinhaAUX-1,ColunaAux,map->ConteudoMapa[LinhaAUX -1][ColunaAux]);
                    //printf("Coluna -1 Mapa:[%d %d] %d \n",LinhaAUX,ColunaAux-1,map->ConteudoMapa[LinhaAUX][ColunaAux-1]);
                    //printf("AUXL ==> %d \n AUXC ==> %d\n",AUXL,AUXC);
                    ColunaAux -=1;
                    LinhaAUX -=1;
                }
            }
                if(AUXL>AUXC){
                    //printf("Dentro do IF!\n");
                    linhaAtual-=1;
                }else{
                    //printf("Dentro do Else!\n");
                    colunaAtual-=1;
                }
            //printf("Final do else: %d %d \n",linhaAtual,colunaAtual);        

        }
    }
    
        est->PontosVidaAtual = est->TabelaPD[linhaAtual][colunaAtual];
        //printf("\nLinha Atual: %d Coluna Atual: %d\n",linhaAtual,colunaAtual);

    }while(est->PontosVidaAtual > 0);


    ApresentarTabelaPD(est, map);
    printf("\n");

    int AUXVIDA = map->VidaJogador;
    for(int i = map->LinhaInicial;i>=0;i--){
        for(int j = map->ColunaInicial;j>=0;j--){
            if(est->TabelaPD[i][j]==0){
                    if(j==map->ColunaInicial){
                        est->TabelaPD[i][j] += est->TabelaPD[i+1][j] + map->ConteudoMapa[i][j];
                    }else{
                        if(i+1<=map->LinhasMapa-1 && j+1<=map->ColunasMapa-1 && est->TabelaPD[i][j+1] + map->ConteudoMapa[i][j] >est->TabelaPD[i+1][j] + map->ConteudoMapa[i][j]){
                            est->TabelaPD[i][j] += est->TabelaPD[i][j+1] + map->ConteudoMapa[i][j];
                        }else if(i+1<=map->LinhasMapa-1 && j+1<=map->ColunasMapa-1 && est->TabelaPD[i][j+1] + map->ConteudoMapa[i][j]<est->TabelaPD[i+1][j]+ map->ConteudoMapa[i][j]){
                            est->TabelaPD[i][j] += est->TabelaPD[i+1][j] + map->ConteudoMapa[i][j];
                        }else if(i+1<=map->LinhasMapa-1 && j+1<=map->ColunasMapa-1){
                            est->TabelaPD[i][j] += est->TabelaPD[i][j+1] + map->ConteudoMapa[i][j];
                        }else if(i==map->LinhaInicial){
                            est->TabelaPD[i][j] += est->TabelaPD[i][j+1] + map->ConteudoMapa[i][j];
                        }
                    }
            }
        }
    }
    est->PontosVidaAtual = est->TabelaPD[map->LinhaFinal][map->ColunaFinal];
    ApresentarTabelaPD(est, map);
    
    printf("\nPontos de vida: %d\n", est->PontosVidaAtual);

    //QUANDO UTILIZADA A CAVERNA2 ESTÁ QUEBRANDO EXATAMENTE NESSA PARTE
    if(est->PontosVidaAtual>0){
         ApresentarTabelaPD(est, map);

        //FazerCaminho(est, map);

        //Imprime(est);

    }

}

void ApresentarTabelaPD(Estudante *ptrAv,MatrizMapa *ptr){
    for(int i = 0;i<ptr->LinhasMapa;i++){
        for(int j = 0;j<ptr->ColunasMapa;j++){
            printf(" [%d] ",ptrAv->TabelaPD[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void FazerCaminho(Estudante *est, MatrizMapa *map,PilhaCoordenadas *PILHA){
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