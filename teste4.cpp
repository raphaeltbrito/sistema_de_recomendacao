#include "leitura.h"
#include "similaridade.h"
#include <iostream>
#include <stdio.h>
#include <ctime>

void liberarIntersecao(Matrizes &matriz) {
    if (matriz.intersecao != NULL) {
        for (int i = 0; i < matriz.nClientes; i++) {
            free(matriz.intersecao[i]);
        }
        free(matriz.intersecao);
        matriz.intersecao = NULL;
    }
}

int main(int argc, char *argv[]) {
    ListaCompras lista;

    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    Matrizes matriz = {}; 

    montarMatrizcompras(lista, matriz);

    if (matriz.compras == NULL){
        printf("Não foi possível construir as matrizes !!");
        liberarMatrizes(matriz);
        return 1;
    }

    clock_t inicio_antigo = clock();
    montarMatriztransposta(matriz);
    montarMatrizintersecao(matriz);
    clock_t fim_antigo = clock();
    double tempo_antigo = double(fim_antigo - inicio_antigo) / CLOCKS_PER_SEC;

    printf("\nTempo no algoritmo antigo (em segundos): %f", tempo_antigo);

    liberarIntersecao(matriz);

    clock_t inicio_novo = clock();
    matriz_multiplica_transposta(matriz);
    clock_t fim_novo = clock();
    double tempo_novo = double(fim_novo - inicio_novo) / CLOCKS_PER_SEC;

    printf("\nTempo no algoritmo novo (em segundos): %f", tempo_novo);

    printf("\nDiferenca de tempo entre algoritmo antigo e algoritmo novo (em segundos): %f" , tempo_antigo - tempo_novo);

    liberarMatrizes(matriz);
    return 0;

}