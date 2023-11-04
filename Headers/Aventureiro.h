#include "PilhaRamificacao.h"
//Contém a tabela armazenando os pontos de vida durante o trajeto.
//Pontos de vida atuais
typedef struct Aventureiro{
    int **TabelaPD;
    int PontosVidaAtual;
}Aventureiro;

void InicializarAventureiro(MatrizMapa *ptrMapa,Aventureiro *ptrAv);
void IniciarDeslocamento(MatrizMapa *ptr,Aventureiro *ptrAv,PilhaCoordenadas *PtrCoordenadas,PilhaRamificado *PtrRamificado,FilaPilhas *Filas);
int Deslocar(MatrizMapa *ptr,Aventureiro *ptrAv,PilhaCoordenadas *PtrCoordenadas,PilhaRamificado *PtrRamificado,FilaPilhas *Filas);
//int ExisteRamificacao(int i,int j,Aventureiro *ptrAv);
int EsquerdaLivre(int j);
int CimaLivre(int i);
void RestaurarMatriz(int *i,int *j,PilhaCoordenadas *PtrCoordenadas,PilhaRamificado *PtrRamificado);
