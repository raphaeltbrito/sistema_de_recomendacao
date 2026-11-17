#include "similaridade.h"
#include <stdlib.h>
#include <stdio.h>

void *reservarMemoria(size_t tamanho) {
    void *memoria = malloc(tamanho);

    if (memoria == NULL) {
        printf("Erro ao reservar memoria.\n");
        exit(EXIT_FAILURE);
    }

    return memoria;
}

void liberarMatrizes(Matrizes &matriz) {
    for (int i = 0; i < matriz.nClientes; i++) {
        if (matriz.compras != NULL) {
            free(matriz.compras[i]);
        }

        if (matriz.intersecao != NULL) {
            free(matriz.intersecao[i]);
        }

        if (matriz.similaridade != NULL) {
            free(matriz.similaridade[i]);
        }
    }

    for (int i = 0; i < matriz.nProdutos; i++) {
        if (matriz.transposta != NULL) {
            free(matriz.transposta[i]);
        }
    }

    free(matriz.compras);
    free(matriz.transposta);
    free(matriz.intersecao);
    free(matriz.similaridade);

    matriz.compras = NULL;
    matriz.transposta = NULL;
    matriz.intersecao = NULL;
    matriz.similaridade = NULL;

    matriz.nClientes = 0;
    matriz.nProdutos = 0;
}

void montarMatrizcompras(const ListaCompras &lista, Matrizes &matriz) {
    liberarMatrizes(matriz);

    int nClientes = lista.cod_clientes.size();
    int nProdutos = lista.cod_produtos.size();

    if (nClientes == 0 || nProdutos == 0) {
        return;
    }

    matriz.nClientes = nClientes;
    matriz.nProdutos = nProdutos;

    matriz.compras = (int **) reservarMemoria(nClientes * sizeof(int *));

    matriz.transposta = (int **) reservarMemoria(nProdutos * sizeof(int *));

    matriz.intersecao = (int **) reservarMemoria(nClientes * sizeof(int *));

    matriz.similaridade = (double **) reservarMemoria(nClientes * sizeof(double *));

    for (int i = 0; i < nClientes; i++) {
        matriz.compras[i] = (int *) reservarMemoria(nProdutos * sizeof(int));

        matriz.intersecao[i] = (int *) reservarMemoria(nClientes * sizeof(int));

        matriz.similaridade[i] = (double *) reservarMemoria(nClientes * sizeof(double));
    }

    for (int i = 0; i < nProdutos; i++) {
        matriz.transposta[i] = (int *) reservarMemoria(nClientes * sizeof(int));
    }

    for (int i = 0; i < nClientes; i++) {
        for (int j = 0; j < nProdutos; j++) {
            matriz.compras[i][j] = 0;
        }
    }

    for (int i = 0; i < nClientes; i++) {
        for (int j = 0; j < lista.prod_clientes[i].size(); j++) {
            int indiceProduto = lista.prod_clientes[i][j];
            matriz.compras[i][indiceProduto] = 1;
        }
    }
}

void montarMatriztransposta(Matrizes &matriz) {
    for (int i = 0; i < matriz.nClientes; i++) {
        for (int j = 0; j < matriz.nProdutos; j++) {
            matriz.transposta[j][i] = matriz.compras[i][j];
        }
    }
}

void montarMatrizintersecao(Matrizes &matriz) {
    for (int i = 0; i < matriz.nClientes; i++) {
        for (int j = 0; j < matriz.nClientes; j++) {
            matriz.intersecao[i][j] = 0;

            for (int k = 0; k < matriz.nProdutos; k++) {
                matriz.intersecao[i][j] +=
                    matriz.compras[i][k] *
                    matriz.transposta[k][j];
            }
        }
    }
}

void montarMatrizsimilaridade(Matrizes &matriz) {
    for (int i = 0; i < matriz.nClientes; i++) {
        for (int j = 0; j < matriz.nClientes; j++) {
            if (matriz.intersecao[i][i] == 0) {
                matriz.similaridade[i][j] = 1.0;
            } else {
                matriz.similaridade[i][j] = 1.0 - ((double) matriz.intersecao[i][j] / 
                matriz.intersecao[i][i]);
            }
        }
    }
}

ResultadoBusca buscarMaisSimilar(
    const Matrizes &matriz, int clienteAlvo
) {
    ResultadoBusca resultado;
    resultado.indiceCliente = -1;
    resultado.valor = 2.0;

    if (clienteAlvo < 0 || clienteAlvo >= matriz.nClientes) {
        return resultado;
    }

    if (matriz.similaridade == NULL) {
        return resultado;
    }

    for (int j = 0; j < matriz.nClientes; j++) {
        if (j == clienteAlvo) {
            continue;
        }

        double valorAtual = matriz.similaridade[clienteAlvo][j];

        if (valorAtual < resultado.valor) {
            resultado.indiceCliente = j;
            resultado.valor = valorAtual;
        }
    }

    return resultado;
}