#ifndef recomendacao_h
#define recomendacao_h
#include "similaridade.h"
#include "leitura.h"

typedef struct {
   int indice_produto_ranking;
   double valor_R;
} ProdutoRanqueado;

bool compararRanking (const ProdutoRanqueado &a , const ProdutoRanqueado &b);

vector <ProdutoRanqueado> RecomendarProdutos(const ListaCompras &lista, const Matrizes &matriz, int cliente_alvo, int numeroRecomendacoes);

vector <ProdutoRanqueado> RecomendarProdutos(const MatrizCSR &compras, const MatrizCSR &intersecao, int cliente_alvo, int numeroRecomendacoes);


#endif