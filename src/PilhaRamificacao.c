#include "..\Headers\PilhaRamificacao.h"

void inicializarRamificacao(PilhaRamificado *ptr){
    ptr->topo = NULL;
}
int estaVazioRamificacao(PilhaRamificado *ptr){
    return ptr->topo==NULL;
}
void pushRamificacao(PilhaRamificado *ptr,int line,int collun,int pontosVida) {
    PontosRamificados *PTRVAR = (PontosRamificados *)malloc(sizeof(PontosRamificados));
    if (PTRVAR == NULL) {
        printf("Ocorreu um erro na alocação de memória.\n");
        return;
    }

    PontosRamificados *PtrVar = ptr->topo;
    while (PtrVar != NULL) {
        if (PtrVar->LinhaRamificada == line && PtrVar->ColunaRamificada == collun) {
            free(PTRVAR); // Liberar memória alocada se já existir na pilha
            return;
        }
        PtrVar = PtrVar->prox;
    }

    PTRVAR->LinhaRamificada = line;
    PTRVAR->ColunaRamificada = collun;
    PTRVAR->Esquerda = -1;
    PTRVAR->Cima = -1;
    PTRVAR->UltimosPontosDeVida = pontosVida;
    PTRVAR->prox = ptr->topo;
    ptr->topo = PTRVAR;
}

void popRamificacao(PilhaRamificado *ptr){
    if(estaVazioRamificacao(ptr)){
        return;
    }
    PontosRamificados *PTRVAR = ptr->topo;
    ptr->topo = PTRVAR->prox;
    free(PTRVAR);
}
void ApresentarRamificacao(PilhaRamificado *ptr){
    if(estaVazioRamificacao(ptr)){
        return;
    }else{
        PontosRamificados *PtrVar = ptr->topo;
        printf("Ramificacoes: ");
        while(PtrVar!=NULL){
            printf(" [%d|%d] Vida: %d \n ", PtrVar->LinhaRamificada, PtrVar->ColunaRamificada,PtrVar->UltimosPontosDeVida);
            PtrVar = PtrVar->prox;
        }
        printf("\n");
    }

}

int EstaPresentePilhaRamificado(PilhaRamificado *ptr, int line, int collun) {
    PontosRamificados *temp = ptr->topo;

    // Percorre a pilha e compara as coordenadas
    while (temp != NULL) {
        if (temp->LinhaRamificada == line && temp->ColunaRamificada == collun) {
            printf("Elemento (%d, %d) encontrado na pilha.\n", line, collun);
            return 1;
        }
        temp = temp->prox;
    }

    printf("Elemento (%d, %d) nao encontrado na pilha.\n", line, collun);
    return 0;
}