#include "../Headers/Pilha.h"
void initialize(PilhaCoordenadas* ptr) {
    ptr->topo = NULL;
}

int isEmpty(PilhaCoordenadas* ptr) {
    return ptr->topo == NULL;
}

void push(PilhaCoordenadas* ptr, int ptrLine, int ptrCollun,int PontosDeVidaAtuais) {
    Coordenadas* PtrVar = (Coordenadas*)malloc(sizeof(Coordenadas));
    if (PtrVar == NULL) {
        printf("Ocorreu um erro na alocação de memória.\n");
        return;
    }
    PtrVar->line = ptrLine;
    PtrVar->collun = ptrCollun;
    ptr->PontosVida = PontosDeVidaAtuais;
    PtrVar->next = ptr->topo;
    ptr->topo = PtrVar;
}
void RestaurarPontosDeVida(PilhaCoordenadas* ptr,MatrizMapa *ptrMapa){
    ptr->PontosVida = ptrMapa->VidaJogador;
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
        printf("Vida: %d\n ",ptr->PontosVida);
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
