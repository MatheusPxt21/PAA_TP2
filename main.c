#include "Headers/PD_Estudante.h"

int main(){
    srand(time(NULL));

    MatrizMapa map;
    Estudante est;
    PilhaCoordenadas ptrCoordenadas;

    LeituraMatriz("MapasExemplo/caverna4.txt",&map);

    ImprimeArquivoLido(&map);
    
    Deslocar(&map,&est,&ptrCoordenadas);
    
    return 0;

}