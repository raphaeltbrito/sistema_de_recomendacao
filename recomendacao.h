#ifndef recomendacao_h
#define recomendacao_h
#include "similaridade.h"
#include "leitura.h"

typedef struct {
   int indice_produto_ranking;
   double valor_R;
} ProdutoRanqueado;

vector <ProdutoRanqueado> RecomendarProdutos(const ListaCompras &lista, const Matrizes &matriz, int cliente_alvo, int k);

bool RecomendarProdutos()

#endif