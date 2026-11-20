#ifndef similaridade_h
#define similaridade_h

#include "leitura.h"

typedef struct {
    int **compras;
    int **transposta;
    int **intersecao;
    double **similaridade;

    int nClientes;
    int nProdutos;
} Matrizes;

typedef struct {
    int indiceCliente;
    double valor;
} ResultadoBusca;

void montarMatrizcompras(const ListaCompras &lista, Matrizes &matriz);

void montarMatriztransposta(Matrizes &matriz);

void montarMatrizintersecao(Matrizes &matriz);

void montarMatrizsimilaridade(Matrizes &matriz);

void matriz_multiplica_transposta(Matrizes &matriz);

void escolher_algoritmo (Matrizes &matriz, int opcao_algoritmo);

ResultadoBusca buscarMaisSimilar(const Matrizes &matriz, int clienteAlvo);

void liberarMatrizes(Matrizes &matriz);

#endif