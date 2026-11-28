#include "leitura.h"
#include "similaridade.h"
#include <iostream>
#include <stdio.h>
#include "recomendacao.h"
#include "esparsa.h"

int main(int argc, char *argv[]) {
    ListaCompras lista;
    MatrizCSR comprasCSR = {};
    MatrizCSR intersecaoCSR = {};
    Matrizes matriz = {};
    
    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    montarComprasCSR(lista,comprasCSR);

    if (comprasCSR.row_ptr == NULL){
        return 1;
    }

    montarIntersecaoCSR (comprasCSR, intersecaoCSR);

    if (intersecaoCSR.row_ptr == NULL){
        LiberarCSR(comprasCSR);
        return 1;
    }

    printf("\n=== INTERSECAO CSR ===\n");
    printf("Linhas: %d\n", intersecaoCSR.nLinhas);
    printf("Elementos nao nulos: %d\n", intersecaoCSR.qntElementosnaoNulos);

    printf("\n=== COMPRAS CSR ===\n");
    printf("Linhas: %d\n", comprasCSR.nLinhas);
    printf("Elementos nao nulos: %d\n", comprasCSR.qntElementosnaoNulos);

    escolher_algoritmo(lista, matriz, comprasCSR, intersecaoCSR);
    
    liberarMatrizes(matriz);
    LiberarCSR(comprasCSR);
    LiberarCSR(intersecaoCSR);

    return 0;
}