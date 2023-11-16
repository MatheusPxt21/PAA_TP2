#include "Headers/PD_Estudante.h"

int main(){
    srand(time(NULL));

    MatrizMapa map;
    LeituraMatriz("MapasExemplo/caverna5.txt",&map);

    Estudante est;

    Deslocar(&map, &est);
    
    return 0;

}