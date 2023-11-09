#include "../Headers/Fila.h"

void initializeFila(Fila* fila) {
    fila->front = fila->rear = NULL;
}

int isEmptyFila(Fila* fila) {
    return (fila->front == NULL);
}

void InserirFila(Fila* fila, int linha, int coluna) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro: memória insuficiente para alocar novo nó.\n");
        exit(1);
    }
    novoNode->linha = linha;
    novoNode->coluna = coluna;
    novoNode->next = NULL;

    if (fila->rear == NULL) {
        fila->front = fila->rear = novoNode;
    } else {
        fila->rear->next = novoNode;
        fila->rear = novoNode;
    }
}

void RetirarFila(Fila* fila) {
    if (isEmptyFila(fila)) {
        printf("Erro: a fila está vazia.\n");
        return;
    }

    Node* temp = fila->front;
    fila->front = fila->front->next;

    if (fila->front == NULL) {
        fila->rear = NULL;
    }

    free(temp);
}

void imprimirFila(Fila* fila) {
    Node* temp = fila->front;
    while (temp != NULL) {
        printf("(%d, %d) ", temp->linha, temp->coluna);
        temp = temp->next;
    }
    printf("\n");
}

void liberarFila(Fila* fila) {
    while (!isEmptyFila(fila)) {
        RetirarFila(fila);
    }
}
