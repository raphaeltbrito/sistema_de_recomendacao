#include "recomendacao.h"
#include "similaridade.h"
#include <stdio.h>
#include <algorithm>

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
