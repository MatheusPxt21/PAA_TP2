#include "fila.h"

// Função para inicializar uma fila vazia
void inicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

// Função para verificar se a fila está vazia
int filaVazia(const Fila* fila) {
    return (fila->frente == NULL);
}

// Função para enfileirar um elemento
void enfileirar(Fila* fila, int x, int y) {
    ElementoFila elemento;
    elemento.x = x;
    elemento.y = y;
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }

    novoNode->elemento = elemento;
    novoNode->proximo = NULL;

    if (filaVazia(fila)) {
        fila->frente = novoNode;
        fila->tras = novoNode;
    } else {
        fila->tras->proximo = novoNode;
        fila->tras = novoNode;
    }
}

// Função para desenfileirar um elemento
ElementoFila desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        fprintf(stderr, "Erro: Tentativa de desenfileirar de uma fila vazia.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = fila->frente;
    ElementoFila elementoDesenfileirado = temp->elemento;

    fila->frente = fila->frente->proximo;
    free(temp);

    if (fila->frente == NULL) {
        fila->tras = NULL;
    }

    return elementoDesenfileirado;
}

// Função para liberar a memória ocupada pela fila
void liberarFila(Fila* fila) {
    while (!filaVazia(fila)) {
        desenfileirar(fila);
    }
}