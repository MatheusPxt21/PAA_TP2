#include "Fila.h"
//Armazenará os pontos de vida do jogador no ponto da ramificação
//Localização da última ramificação
//Direções válidas, inicializados como -1
//Terá muitas ramificações já que o mapa não terá obstáculos.
//Se a vida chegar ao ponto de ser ≤ 0, o elemento será retirado.
typedef struct PontosRamificados{
    int UltimosPontosDeVida;
    int ColunaRamificada,LinhaRamificada;
    int Esquerda,Cima;
    struct PontosRamificados *prox;
}PontosRamificados;

typedef struct PilhaRamificado{

    PontosRamificados *topo;

}PilhaRamificado;

void inicializarRamificacao(PilhaRamificado *ptr);

int estaVazioRamificacao(PilhaRamificado *ptr);

void pushRamificacao(PilhaRamificado *ptr,int line,int collun,int pontosVida);

void popRamificacao(PilhaRamificado *ptr);

int EstaPresentePilhaRamificado(PilhaRamificado *ptr,int line ,int collun);

void ApresentarRamificacao(PilhaRamificado *ptr);

void LiberarRamificacao(PilhaRamificado *ptr);