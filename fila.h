#include <stdio.h>
#include <stdlib.h>

// Definição da struct para os elementos da fila
typedef struct {
    int x;
    int y;
} ElementoFila;

// Definição do nó da fila
typedef struct Node {
    ElementoFila elemento;
    struct Node* proximo;
} Node;

// Definição da fila
typedef struct {
    Node* frente;
    Node* tras;
} Fila;

void inicializarFila(Fila* fila);
int filaVazia(const Fila* fila);
void enfileirar(Fila* fila, int x, int y);
ElementoFila desenfileirar(Fila* fila);
void liberarFila(Fila* fila);
