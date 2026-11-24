#include "recomendacao.h"
#include "similaridade.h"
#include <stdio.h>
#include <algorithm>
using namespace std;

bool compararRanking (const ProdutoRanqueado &a , const ProdutoRanqueado &b) {
    return a.valor_R < b.valor_R;
}

vector <ProdutoRanqueado> RecomendarProdutos(const ListaCompras &lista, const Matrizes &matriz, int cliente_alvo, int numeroRecomendacoes){
    vector <int> indices_vizinhos;
    vector <ProdutoRanqueado> vetor_R;
    vector <ProdutoRanqueado> recomendados;

    if( numeroRecomendacoes <= 0 || cliente_alvo < 0 || cliente_alvo >= matriz.nClientes){
        return recomendados;
    }
    for (int numero_vizinho = 0; numero_vizinho < matriz.nClientes; numero_vizinho++) {
        if ( numero_vizinho == cliente_alvo) {
            continue;
        }

        double valor_similaridade = matriz.similaridade[cliente_alvo][numero_vizinho];
        if (valor_similaridade < 1){
            indices_vizinhos.push_back(numero_vizinho);
        }
    }

    for (int i = 0; i < lista.cod_produtos.size(); i++){
        ProdutoRanqueado pr;
        pr.indice_produto_ranking = i;
        pr.valor_R = 1;
        vetor_R.push_back(pr);
    }

    for (int i = 0; i < indices_vizinhos.size(); i++){
        int vizinho = indices_vizinhos[i];
        double valor = matriz.similaridade[cliente_alvo][vizinho];
        for (int j = 0; j < lista.cod_produtos.size(); j++){
            if (matriz.compras[vizinho][j] == 1 && matriz.compras[cliente_alvo][j] == 0){
                vetor_R[j].valor_R = vetor_R[j].valor_R * valor;
            }
        }
    }

    sort(vetor_R.begin(), vetor_R.end(),compararRanking);

    for (int i = 0; i < vetor_R.size() && recomendados.size() < numeroRecomendacoes; i++){
        int produto = vetor_R[i].indice_produto_ranking;
        if (matriz.compras[cliente_alvo][produto] == 0 && vetor_R[i].valor_R < 1){
            recomendados.push_back(vetor_R[i]);
        }

    }

    return recomendados;
}
vector<ProdutoRanqueado> RecomendarProdutos(const MatrizCSR &compras,const MatrizCSR &intersecao,int cliente_alvo,int numeroRecomendacoes) {
    vector<ProdutoRanqueado> vetor_R;
    vector<ProdutoRanqueado> recomendados;

    if (numeroRecomendacoes <= 0 || cliente_alvo < 0 || cliente_alvo >= compras.nLinhas) {
        return recomendados;
    }

    for (int produto = 0; produto < compras.nColunas; produto++) {
        ProdutoRanqueado pr;
        pr.indice_produto_ranking = produto;
        pr.valor_R = 1.0;
        vetor_R.push_back(pr);
    }

    for (int vizinho = 0; vizinho < compras.nLinhas; vizinho++) {
        if (vizinho == cliente_alvo) {
            continue;
        }

        double distancia = calcularDistanciaCSR(intersecao, cliente_alvo, vizinho);

        if (distancia >= 1.0) {
            continue;
        }

        
        int inicio = compras.row_ptr[vizinho];
        int fim = compras.row_ptr[vizinho + 1];

        for (int p = inicio; p < fim; p++) {
            int produto = compras.col_index[p];

            if (consultarValorCSR(compras, cliente_alvo, produto) == 0.0) {
                vetor_R[produto].valor_R *= distancia;
            }
        }
    }

    sort(vetor_R.begin(), vetor_R.end(), compararRanking);

   for (int i = 0; i < compras.nColunas; i++) {
    if (vetor_R[i].valor_R < 1.0) {
        recomendados.push_back(vetor_R[i]);
        numeroRecomendacoes--;

        if (numeroRecomendacoes == 0) {
            break;
        }
    }
   }
   
    return recomendados;
}
