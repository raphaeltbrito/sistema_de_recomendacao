#include "leitura.h"
#include "similaridade.h"
#include <stdio.h>
#include <ctime>

int main(int argc, char *argv[]){
    ListaCompras lista;
    Matrizes matriz = {};

    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    montarMatrizcompras(lista, matriz);
    calcular_tempo(matriz);

    liberarMatrizes(matriz);
    return 0;
}