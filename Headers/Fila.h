#include "Pilha.h"

//FILA DE Pilhas > Ira armazenar os caminhos válidos, escolher com o maior PontosVida

typedef struct Node {
    PilhaCoordenadas pilha;
    struct Node* next;
} Node;

typedef struct FilaPilhas {
    Node* front;
    Node* rear;
} FilaPilhas;

void initializeFilaPilhas(FilaPilhas* fila);
int isEmptyFilaPilhas(FilaPilhas* fila);
int pilhaEqual(PilhaCoordenadas* pilha1, PilhaCoordenadas* pilha2);
void InserirFilaPilhas(FilaPilhas* fila, PilhaCoordenadas* pilha);
void RetirarFilaPilhas(FilaPilhas* fila);
void imprimirFilaPilhas(FilaPilhas* fila);
void liberarFilaPilhas(FilaPilhas* fila);