#include "similaridade.h"
#include <stdlib.h>
#include <stdio.h>

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

    matriz.compras = (int**) malloc(sizeof(int *) * nClientes);

    if (matriz.compras == NULL) {
        printf("Falha ao alocar a matriz das compras !!! ");
        matriz.nClientes = 0;
        matriz.nProdutos = 0;
        return;
    }

    for (int i = 0; i < nClientes; i++){
        matriz.compras[i] = NULL;
    }

    for (int i = 0; i < nClientes; i++){
        matriz.compras[i] = (int *) malloc (sizeof(int) * nProdutos);
        if (matriz.compras[i] == NULL){
            printf("Falha ao alocar a linha %d da matriz de compras!!", i);
            liberarMatrizes(matriz);
            return;
        }
    }

    for (int i = 0; i < nClientes; i++){
        for (int j = 0; j < nProdutos; j++){
            matriz.compras[i][j] = 0;
        }
    }

    for (int i = 0; i < nClientes; i++){
        for (int j = 0; j < lista.prod_clientes[i].size(); j++) {
            int indiceProduto = lista.prod_clientes[i][j];
            matriz.compras[i][indiceProduto] = 1;
        }
    }
}

void montarMatriztransposta(Matrizes &matriz) {
    if (matriz.nClientes == 0 || matriz.nProdutos == 0){
        return;
    }

    matriz.transposta = (int**) malloc(sizeof(int *) * matriz.nProdutos);

    if (matriz.transposta == NULL) {
        printf("Falha ao alocar a matriz transposta !!! ");
        liberarMatrizes(matriz);
        return;
    }

    for (int i = 0 ; i < matriz.nProdutos ; i++){
        matriz.transposta[i] = NULL;
    }

    for (int i = 0 ; i < matriz.nProdutos; i++) {
        matriz.transposta[i] = (int *) malloc (sizeof(int) * matriz.nClientes);
        if (matriz.transposta[i] == NULL){
                printf("Falha ao alocar a linha %d da matriz transposta!!", i);
                liberarMatrizes(matriz);
                return;
        }
    }

    for (int i = 0; i < matriz.nClientes; i++) {
        for (int j = 0; j < matriz.nProdutos; j++){
            matriz.transposta[j][i] = matriz.compras[i][j];
        }
    }
}

void montarMatrizintersecao(Matrizes &matriz) {
    if (matriz.nClientes == 0 || matriz.nProdutos == 0){
        return;
    }
    
    matriz.intersecao = (int**) malloc(sizeof(int *) * matriz.nClientes);

    if (matriz.intersecao == NULL) {
        printf("Falha ao alocar a matriz intersecao !!! ");
        liberarMatrizes(matriz);
        return;
    }

    for (int i = 0; i < matriz.nClientes; i++){
        matriz.intersecao[i] = NULL;
    }
    for (int i = 0 ; i < matriz.nClientes; i++) {
        matriz.intersecao[i] = (int *) malloc (sizeof(int) * matriz.nClientes);
        if (matriz.intersecao[i] == NULL){
                printf("Falha ao alocar a linha %d da matriz intersecao!!", i);
                liberarMatrizes(matriz);
                return;
        }
    }

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

void matriz_multiplica_transposta(Matrizes &matriz){
    if (matriz.nClientes == 0 || matriz.nProdutos == 0){
        return;
    }
    
    matriz.intersecao = (int**) malloc(sizeof(int *) * matriz.nClientes);

    if (matriz.intersecao == NULL) {
        printf("Falha ao alocar a matriz intersecao !!! ");
        liberarMatrizes(matriz);
        return;
    }

    for (int i = 0; i < matriz.nClientes; i++){
        matriz.intersecao[i] = NULL;
    }
    for (int i = 0 ; i < matriz.nClientes; i++) {
        matriz.intersecao[i] = (int *) malloc (sizeof(int) * matriz.nClientes);
        if (matriz.intersecao[i] == NULL){
                printf("Falha ao alocar a linha %d da matriz intersecao!!", i);
                liberarMatrizes(matriz);
                return;
        }
    }

    matriz.nClientes;
    matriz.nProdutos;
    matriz.intersecao;

    for (int i = 0; i < matriz.nClientes; i++){
        for (int j = i; j <matriz.nClientes; j++){
            int produtos_em_comum = 0;
            for (int k = 0; k < matriz.nProdutos; k++){
                produtos_em_comum = produtos_em_comum + matriz.compras[i][k] * matriz.compras[j][k];
            }
            matriz.intersecao[i][j] = produtos_em_comum;
            matriz.intersecao[j][i] = produtos_em_comum;
        }
    }
}

void escolher_algoritmo (Matrizes &matriz, int opcao_algoritmo){
    printf("digite a opcao do algoritmo:");
    scanf("%d", &opcao_algoritmo);
    
    if (opcao_algoritmo == 1){
        montarMatriztransposta(matriz);
        montarMatrizintersecao(matriz);
    } else if (opcao_algoritmo == 2){
        matriz_multiplica_transposta(matriz);
    } else {
        printf("escolha de numero invalida");
    }
}

void montarMatrizsimilaridade(Matrizes &matriz) {
    if (matriz.nClientes == 0 || matriz.nProdutos == 0){
        return;
    }
    
    matriz.similaridade = (double**) malloc(sizeof(double *) * matriz.nClientes);

    if (matriz.similaridade == NULL) {
        printf("Falha ao alocar a matriz similaridade !!! ");
        liberarMatrizes(matriz);
        return;
    }

    for (int i = 0; i < matriz.nClientes; i++){
        matriz.similaridade[i] = NULL;
    }

    for (int i = 0 ; i < matriz.nClientes; i++) {
        matriz.similaridade[i] = (double *) malloc (sizeof(double) * matriz.nClientes);
        if (matriz.similaridade[i] == NULL){
                printf("Falha ao alocar a linha %d da matriz similaridade!!", i);
                liberarMatrizes(matriz);
                return;
        }
    }

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

ResultadoBusca buscarMaisSimilar(const Matrizes &matriz, int clienteAlvo) {
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