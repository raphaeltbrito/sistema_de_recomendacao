#include "similaridade.h"

using namespace std;

void montarMatrizcompras(const ListaCompras &lista, Matrizes &matriz) {
    int nClientes = lista.cod_clientes.size(), nProdutos = lista.cod_produtos.size();
    vector<int> linha;
    matriz.compras.clear();
    for (int i = 0; i < nProdutos ; i++) {
        linha.push_back(0);
    }
    for (int i = 0; i < nClientes; i++) {
        matriz.compras.push_back(linha);
    }
    for (int i = 0; i < nClientes; i++){
        for (int j = 0; j < lista.prod_clientes[i].size(); j++) {
            int indiceProduto = lista.prod_clientes[i][j];
            matriz.compras[i][indiceProduto] = 1;
        }
    }
}

void montarMatriztransposta(Matrizes &matriz) {
    matriz.transposta.clear();
    if (matriz.compras.size() == 0){
        return;
    }
    int nClientes = matriz.compras.size();
    int nProdutos = matriz.compras[0].size();

    vector<int> linha;

    for (int i = 0; i < nClientes ; i++) {
        linha.push_back(0);
    }

    for (int i = 0; i < nProdutos; i++) {
        matriz.transposta.push_back(linha);
}

    for (int i = 0; i < nClientes; i++){
        for (int j = 0; j < nProdutos; j++) {
            matriz.transposta[j][i] = matriz.compras[i][j];
        }
    }
}

void montarMatrizintersecao(Matrizes &matriz) {
    matriz.intersecao.clear();
    if (matriz.compras.size() == 0){
        return;
    }
    int nClientes = matriz.compras.size();
    int nProdutos = matriz.compras[0].size();
    
    vector<int> linha;
    for (int i = 0 ; i < nClientes; i++) {
        linha.push_back(0);
    }
    for (int i = 0 ; i < nClientes; i++) {
        matriz.intersecao.push_back(linha);
    }
   for (int i = 0; i < nClientes ; i++) {
        for(int j = 0 ; j < nClientes; j++) {
            for (int k = 0; k < nProdutos; k++){
                 matriz.intersecao[i][j] += matriz.compras[i][k] * matriz.transposta[k][j];
            }
        }
   }
    
}
void montarMatrizsimilaridade(Matrizes &matriz) {
    matriz.similaridade.clear();
    if (matriz.intersecao.size() == 0) {
        return;
    }

    int nClientes = matriz.intersecao.size();

    vector<double> linha;

    for (int i = 0; i < nClientes; i++){
        linha.push_back(0);
    }
    for (int i = 0; i < nClientes; i++){
        matriz.similaridade.push_back(linha);
    }
    for (int i = 0; i < nClientes; i++){
        for (int j = 0; j < nClientes; j++){
            if (matriz.intersecao[i][i] == 0) {
                matriz.similaridade[i][j] = 1.0;
            } else {
                 matriz.similaridade[i][j] = 1 - ((double) matriz.intersecao[i][j]/matriz.intersecao[i][i]);

            }
        }
    }
}

ResultadoBusca buscarMaisSimilar(const Matrizes &matriz, int clienteAlvo) {
    ResultadoBusca resultado;
    resultado.indiceCliente = -1;
    resultado.valor = 2.0;

    int nClientes = matriz.similaridade.size();

    if (clienteAlvo < 0 || clienteAlvo >= nClientes){
        printf("Nenhum cliente encontrado");
        return resultado;
    }

    for (int j = 0; j < nClientes; j++) {
        if ( j == clienteAlvo) {
            continue;
        }

        double valorAtual = matriz.similaridade[clienteAlvo][j];

        if (valorAtual < resultado.valor){
            resultado.indiceCliente = j;
            resultado.valor = valorAtual;
        }
        
        
    }
    return resultado;
}