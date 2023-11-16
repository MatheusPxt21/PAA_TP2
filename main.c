#include "Headers/PD_Estudante.h"

int main(){
    srand(time(NULL));

    MatrizMapa map;
    Estudante est;

    LeituraMatriz("MapasExemplo/caverna4.txt",&map);

    ImprimeArquivoLido(&map);

    //printf("\nPontos de vida: %d\n", map.VidaJogador);
    

    Deslocar(&map, &est);
    
    return 0;

}