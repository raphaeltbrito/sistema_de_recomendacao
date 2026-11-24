#ifndef esparsa_h
#define esparsa_h
#include "leitura.h"

typedef struct {
    double *values;
    int *col_index;
    int *row_ptr;
    int nLinhas; 
    int nColunas;
    int qntElementosnaoNulos;
}MatrizCSR;

void LiberarCSR (MatrizCSR &matriz);

void montarComprasCSR (const ListaCompras &lista, MatrizCSR &matriz);

double produtoLinhasCSR(const MatrizCSR &matriz, int LinhaA, int LinhaB);

void montarIntersecaoCSR (const MatrizCSR &matriz, MatrizCSR &intersecao);

double consultarValorCSR(const MatrizCSR &matriz, int linha, int coluna);

#endif