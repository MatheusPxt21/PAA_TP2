#include "Fila.h"

//Contém a tabela armazenando os pontos de vida durante o trajeto.
//Pontos de vida atuais
typedef struct Aventureiro{
    int **TabelaPD;
    int PontosVidaAtual;
}Aventureiro;

void InicializarAventureiro(MatrizMapa *ptrMapa, Aventureiro *ptrAv);
void IniciarDeslocamento(MatrizMapa *ptr,Aventureiro *ptrAv,Fila *Filas);
int Deslocar(MatrizMapa *ptr, Aventureiro *ptrAv, Fila *Filas);
int EsquerdaLivre(int i,int j,Aventureiro *ptrAv,MatrizMapa *ptr);
int CimaLivre(int i,int j,Aventureiro *ptrAv,MatrizMapa *ptr);
int EscolherMelhorCaminho(int i,Aventureiro *ptrAv,MatrizMapa *ptr);
void ApresentarTabelaPD(Aventureiro *ptrAv,MatrizMapa *ptr);
void PreencherFila(MatrizMapa *ptr,Aventureiro *ptrAv,Fila *fila);
void EscreverArquivoDeSaida(Fila *fila);
void EscreverArquivoDeSaidaErro();
