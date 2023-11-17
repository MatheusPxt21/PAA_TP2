#include "../Headers/Pilha.h"

typedef struct Estudante{
    int **TabelaPD;
    int PontosVidaAtual;
    int *Caminho;
}Estudante;

void InicializarEstudante(MatrizMapa *ptrMapa,Estudante *ptrAv);

void Deslocar(MatrizMapa *map, Estudante *est, PilhaCoordenadas *pilha);

void ApresentarTabelaPD(Estudante *ptrAv,MatrizMapa *ptr);

void FazerCaminho(Estudante *est, MatrizMapa *map,PilhaCoordenadas *PILHA);

void Resultado(PilhaCoordenadas *ptrPilha);

void EscreverArquivoDeSaidaErro();

void Imprime(Estudante *est);

