#include "../Headers/Fila.h"

void initializeFilaPilhas(FilaPilhas* fila) {
    fila->front = NULL;
    fila->rear = NULL;
}

int isEmptyFilaPilhas(FilaPilhas* fila) {
    return fila->front == NULL;
}

int pilhaEqual(PilhaCoordenadas* pilha1, PilhaCoordenadas* pilha2) {

    Coordenadas* temp1 = pilha1->topo;
    Coordenadas* temp2 = pilha2->topo;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->line != temp2->line || temp1->collun != temp2->collun) {
            return 0;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 1;
}

void InserirFilaPilhas(FilaPilhas* fila, PilhaCoordenadas* pilha,int PontosVida) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro: Memória insuficiente\n");
        return;
    }

    PilhaCoordenadas* novaPilha = (PilhaCoordenadas*)malloc(sizeof(PilhaCoordenadas));
    if (novaPilha == NULL) {
        printf("Erro: Memória insuficiente\n");
        free(novoNode);
        return;
    }

    initialize(novaPilha);

    Coordenadas* temp = pilha->topo;
    while (temp != NULL) {
        push(novaPilha, temp->line, temp->collun,PontosVida);
        temp = temp->next;
    }

    novoNode->pilha = *novaPilha;
    novoNode->next = NULL;

    // Não libere a memória alocada para a nova pilha aqui

    if (isEmptyFilaPilhas(fila)) {
        fila->front = novoNode;
        fila->rear = novoNode;
    } else {
        Node* temp2 = fila->front;
        while (temp2 != NULL) {
            if (pilhaEqual(&(temp2->pilha), pilha)) {
                free(novoNode);
                return;
            }
            temp2 = temp2->next;
        }
        fila->rear->next = novoNode;
        fila->rear = novoNode;
    }
}

void RetirarFilaPilhas(FilaPilhas* fila) {
    if (!isEmptyFilaPilhas(fila)) {
        Node* temp = fila->front;
        fila->front = fila->front->next;
        free(temp);
    }
}

void imprimirFilaPilhas(FilaPilhas* fila) {
    Node* temp = fila->front;
    while (temp != NULL) {
        ApresentarCoordenadas(&(temp->pilha));
        temp = temp->next;
    }
}

void pilhaComMaiorHP(FilaPilhas* fila) {
    if (isEmptyFilaPilhas(fila)) {
        printf("Fila de pilhas vazia\n");
        return;
    }

    int maiorPontosVida = fila->front->pilha.PontosVida;
    Node* temp = fila->front;
    Node* pilhaMaiorHP = temp;

    while (temp != NULL) {
        if (temp->pilha.PontosVida > maiorPontosVida) {
            maiorPontosVida = temp->pilha.PontosVida;
            pilhaMaiorHP = temp;
        }
        temp = temp->next;
    }

    printf("Pilha com maior HP:\n");
    ApresentarCoordenadas(&(pilhaMaiorHP->pilha));
}


void liberarFilaPilhas(FilaPilhas* fila) {
    while (!isEmptyFilaPilhas(fila)) {
        PilhaCoordenadas* pilhaParaLiberar = &(fila->front->pilha);
        LiberarPilha(pilhaParaLiberar);
        RetirarFilaPilhas(fila);
    }
}