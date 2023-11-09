#include "LeituraArquivo.h"

typedef struct Coordenadas {

    int line, collun;
    struct Coordenadas* next;

} Coordenadas;

typedef struct PilhaCoordenadas {
    Coordenadas* topo;
} PilhaCoordenadas;

void initialize(PilhaCoordenadas* ptr);
int isEmpty(PilhaCoordenadas* ptr);
void push(PilhaCoordenadas* ptr, int ptrLine, int ptrCollun);
void pop(PilhaCoordenadas* ptr);
void ApresentarCoordenadas(PilhaCoordenadas* ptr);
void LiberarPilha(PilhaCoordenadas* ptr);

