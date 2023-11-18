#include "../Headers/Pilha.h"

void initialize(PilhaCoordenadas* ptr) {
    ptr->topo = NULL;
}

int isEmpty(PilhaCoordenadas* ptr) {
    return ptr->topo == NULL;
}

int existeCoordenadas(PilhaCoordenadas* ptr, int ptrLine, int ptrCollun) {
    Coordenadas* atual = ptr->topo;

    while (atual != NULL) {
        if (atual->line == ptrLine && atual->collun == ptrCollun) {
            // Coordenadas já existem na pilha
            return 1;
        }
        atual = atual->next;
    }

    // Coordenadas não encontradas na pilha
    return 0;
}

void push(PilhaCoordenadas* ptr, int ptrLine, int ptrCollun) {
    // Verifica se as coordenadas já existem na pilha
    if (existeCoordenadas(ptr, ptrLine, ptrCollun)) {
        return;
    }

    // Aloca memória para o novo elemento
    Coordenadas* PtrVar = (Coordenadas*)malloc(sizeof(Coordenadas));
    if (PtrVar == NULL) {
        printf("Ocorreu um erro na alocação de memória.\n");
        return;
    }

    // Preenche as coordenadas do novo elemento
    PtrVar->line = ptrLine;
    PtrVar->collun = ptrCollun;
    PtrVar->next = ptr->topo;

    // Atualiza o topo da pilha
    ptr->topo = PtrVar;
}

void pop(PilhaCoordenadas* ptr) {
    if (isEmpty(ptr)) {
        return;
    }
    Coordenadas* PtrVar = ptr->topo;
    ptr->topo = PtrVar->next;
    free(PtrVar);
}

void ApresentarCoordenadas(PilhaCoordenadas* ptr) {
    if (isEmpty(ptr)) {
        printf("Pilha vazia\n");
    } else {
        Coordenadas* PtrVar = ptr->topo;
        printf("Coordenadas: ");
        while (PtrVar != NULL) {
            printf("[%d|%d] ", PtrVar->line, PtrVar->collun);
            PtrVar = PtrVar->next;
        }
        printf("\n");
    }
}

void LiberarPilha(PilhaCoordenadas* ptr) {
    while (!isEmpty(ptr)) {
        pop(ptr);
    }
}
