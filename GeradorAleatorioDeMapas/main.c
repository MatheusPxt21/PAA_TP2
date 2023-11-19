#include "Headers/MatrizAleatoria.h"

int main() {
    srand(time(NULL));

    MatrizMapa map;
    
    GerarCavernaAleatoria(&map);

    return 0;
}