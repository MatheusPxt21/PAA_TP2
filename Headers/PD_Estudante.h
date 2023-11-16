#include "../Headers/LeituraArquivo.h"

typedef struct Estudante{
    int **TabelaPD;
    int PontosVidaAtual;
}Estudante;

void InicializarEstudante(MatrizMapa *ptrMapa,Estudante *ptrAv);
//void IniciarDeslocamento(MatrizMapa *ptr,Estudante *ptrAv,PilhaCoordenadas *PtrCoordenadas,Fila *Filas);
//int Deslocar(MatrizMapa *ptr, Estudante *ptrAv, PilhaCoordenadas *PtrCoordenadas, Fila *Filas);
int EsquerdaLivre(int i,int j,Estudante *ptrAv,MatrizMapa *ptr);
int CimaLivre(int i,int j,Estudante *ptrAv,MatrizMapa *ptr);
int EscolherMelhorCaminho(int i,Estudante *ptrAv,MatrizMapa *ptr);
void ApresentarTabelaPD(Estudante *ptrAv,MatrizMapa *ptr);
//void PreencherFila(MatrizMapa *ptr,Estudante *ptrAv,Fila *fila);
//void EscreverArquivoDeSaida(Fila *fila);
void EscreverArquivoDeSaidaErro();


void Deslocar(MatrizMapa *map, Estudante *est);
