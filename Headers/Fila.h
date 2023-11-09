#include "Pilha.h"

typedef struct Node {
    int linha,coluna;
    struct Node* next;
} Node;

typedef struct Fila {
    Node* front;
    Node* rear;
} Fila;

void initializeFila(Fila* fila);
int isEmptyFila(Fila* fila);
void InserirFila(Fila* fila, int linha,int coluna);
void RetirarFila(Fila* fila);
void imprimirFila(Fila* fila);
void liberarFila(Fila* fila);