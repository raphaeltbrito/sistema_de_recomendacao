#include "esparsa.h"
#include <stdlib.h>
#include "leitura.h"
#include <algorithm>

using namespace std;

void LiberarCSR (MatrizCSR &matriz) {
    free(matriz.values);
    free(matriz.col_index);
    free(matriz.row_ptr);

    matriz.values = NULL;
    matriz.col_index = NULL;
    matriz.row_ptr = NULL;

    matriz.nLinhas = 0;
    matriz.nColunas = 0;
    matriz.qntElementosnaoNulos = 0;

}

void montarComprasCSR (const ListaCompras &lista, MatrizCSR &matriz) {
    LiberarCSR(matriz);

    matriz.nLinhas = lista.cod_clientes.size();
    matriz.nColunas = lista.cod_produtos.size();
    
    matriz.row_ptr = (int*) malloc((matriz.nLinhas + 1) * sizeof(int));

    if (matriz.row_ptr == NULL) {
        printf("ERRO ao alocar memoria para row_ptr\n");
        LiberarCSR(matriz);
        return;
    }

    matriz.row_ptr[0] = 0;
    for (int cliente = 0; cliente < matriz.nLinhas; cliente++){
       int quantidadeCompras = lista.prod_clientes[cliente].size();

       if (quantidadeCompras == 0){
        matriz.row_ptr[cliente + 1] = matriz.row_ptr[cliente];
        continue;
       }

       int *produtosTemporarios = (int *) malloc (quantidadeCompras * sizeof(int));

       if (produtosTemporarios == NULL){
        printf("ERRO ao alocar memoria para os produtos temporarios\n");
        LiberarCSR(matriz);
        return;
       }

       for (int compra = 0; compra < quantidadeCompras; compra++){
        produtosTemporarios[compra] = lista.prod_clientes[cliente][compra];
       }
       sort(produtosTemporarios, produtosTemporarios + quantidadeCompras);

       int quantidadeProdutosUnicos = 1;
       for (int compra = 1; compra < quantidadeCompras; compra++) {
            if (produtosTemporarios[compra] != produtosTemporarios[compra - 1]) {
                quantidadeProdutosUnicos++;
            }
       }
    matriz.row_ptr[cliente + 1] = matriz.row_ptr[cliente] + quantidadeProdutosUnicos;
    free(produtosTemporarios);
    }
    matriz.qntElementosnaoNulos = matriz.row_ptr[matriz.nLinhas];
    if (matriz.qntElementosnaoNulos == 0){
        return;
    }

    matriz.values = (double *) malloc(matriz.qntElementosnaoNulos * sizeof(double));
    matriz.col_index = (int *) malloc(matriz.qntElementosnaoNulos * sizeof(int));

    if (matriz.values == NULL || matriz.col_index == NULL) {
        printf("ERRO ao alocar memoria para values ou col_index\n");
        LiberarCSR(matriz);
        return;
    }
    for (int cliente = 0; cliente < matriz.nLinhas; cliente++) {
        int quantidadeCompras = lista.prod_clientes[cliente].size();
        if (quantidadeCompras == 0){
            continue;
        }

        int *produtosTemporarios = (int *) malloc (quantidadeCompras * sizeof(int));
        if (produtosTemporarios == NULL) {
            printf("Erro ao alocar a matriz de produtos temporarios\n");
            LiberarCSR(matriz);
            return;
        }

         for (int compra = 0; compra < quantidadeCompras; compra++) {
            produtosTemporarios[compra] = lista.prod_clientes[cliente][compra];
        }
        sort(produtosTemporarios, produtosTemporarios + quantidadeCompras);
        
        int posicao = matriz.row_ptr[cliente];

        matriz.col_index[posicao] = produtosTemporarios[0];
        matriz.values[posicao] = 1.0;
        posicao++;

        for (int compra = 1; compra < quantidadeCompras; compra++){
            if (produtosTemporarios[compra] != produtosTemporarios [compra - 1]) {
                matriz.col_index[posicao] = produtosTemporarios[compra];
                matriz.values[posicao] = 1.0;
                posicao++;
            }
        }
        free(produtosTemporarios);
    }
}

double produtoLinhasCSR(const MatrizCSR &matriz, int LinhaA, int LinhaB){
    double soma = 0.0;
    int p = matriz.row_ptr[LinhaA];
    int q = matriz.row_ptr[LinhaB];

    int fimA = matriz.row_ptr[LinhaA + 1];
    int fimB = matriz.row_ptr[LinhaB + 1];

    while (p < fimA && q < fimB) {
        if (matriz.col_index[p] == matriz.col_index[q]) {
            soma += matriz.values[p] * matriz.values[q];
            p++;
            q++;
        } else if (matriz.col_index[p] < matriz.col_index[q]) {
            p++;
        } else {
            q++;
        }
    }
    return soma; 
}

void montarIntersecaoCSR (const MatrizCSR &matriz, MatrizCSR &intersecao){
    LiberarCSR (intersecao);
    intersecao.nLinhas = matriz.nLinhas;
    intersecao.nColunas = matriz.nLinhas;
    intersecao.row_ptr = (int *) malloc((intersecao.nLinhas + 1) * sizeof(int));
    if (intersecao.row_ptr == NULL) {
        LiberarCSR(intersecao);
        printf("ERRO ao alocar a memoria da matriz intersecao CSR");
        return;
    }
    intersecao.row_ptr[0] = 0;
    for (int i = 0; i < intersecao.nLinhas; i++) {
        int quantidade = 0;
        for (int j = 0; j < intersecao.nColunas; j++) {
            double produto = produtoLinhasCSR(matriz, i , j);
            if (produto != 0.0) {
                quantidade++;
            }
        }
        intersecao.row_ptr[i + 1] = intersecao.row_ptr[i] + quantidade;
    }
    intersecao.qntElementosnaoNulos = intersecao.row_ptr[intersecao.nLinhas];
    if (intersecao.qntElementosnaoNulos == 0) {
        return;
    }

    intersecao.values = (double *) malloc(intersecao.qntElementosnaoNulos * sizeof(double));
    intersecao.col_index = (int *) malloc(intersecao.qntElementosnaoNulos * sizeof(int));

    if (intersecao.values == NULL || intersecao.col_index == NULL) {
        LiberarCSR(intersecao);
        printf("ERRO ao alocar memoria para values ou col_index da matriz intersecao\n");
        return;
    }
    for (int i = 0; i < intersecao.nLinhas; i++) {
        int posicao = intersecao.row_ptr[i];
        for (int j = 0; j < intersecao.nColunas; j++) {
            double produto = produtoLinhasCSR(matriz,i,j);
            if (produto != 0.0) {
                intersecao.values[posicao] = produto;
                intersecao.col_index[posicao] = j;
                posicao++;
            }
        }
    }

}