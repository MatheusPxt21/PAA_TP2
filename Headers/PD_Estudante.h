#include "../Headers/LeituraArquivo.h"

typedef struct Estudante{
    int **TabelaPD;
    int PontosVidaAtual;
    int *Caminho;
}Estudante;

void InicializarEstudante(MatrizMapa *ptrMapa,Estudante *ptrAv);

void Deslocar(MatrizMapa *map, Estudante *est);

void ApresentarTabelaPD(Estudante *ptrAv,MatrizMapa *ptr);

void FazerCaminho(Estudante *est, MatrizMapa *map);

void EscreverArquivoDeSaidaErro();

void Imprime(Estudante *est);
