#include "leitura.h"
#include "similaridade.h"
#include <iostream>
#include <stdio.h>
#include "recomendacao.h"

int main(int argc, char *argv[]) {
    ListaCompras lista;

    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    Matrizes matriz;

    montarMatrizcompras(lista, matriz);

    montarMatriztransposta(matriz);

    montarMatrizintersecao(matriz);

    montarMatrizsimilaridade(matriz);

    string clientes_teste[3] = {"99CL9Y01", "9O6OSM01", "99EF7201"};

    for (int i = 0; i < 3; i++) {
        string cliente_alvo = clientes_teste[i];

        if (lista.map_clientes.find(cliente_alvo) != lista.map_clientes.end()) {
            int indice_cliente = lista.map_clientes[cliente_alvo];
            ResultadoBusca resultado = buscarMaisSimilar(matriz, indice_cliente);
            printf("\nCliente: %s \nProdutos (nomes):\n", cliente_alvo.c_str());

            if (resultado.indiceCliente != -1){
                printf("O cliente mais similar (indice): %d | Distancia: %.3f\n", resultado.indiceCliente, resultado.valor);
            } else {
                printf ("Nao ha' outro cliente para comparar\n");
            }

            vector<int> produtos = lista.prod_clientes[indice_cliente];
            for (int id_prod : produtos) {
                string nome_externo = lista.nome_produtos[id_prod];
                printf("  Produto: %s\n", nome_externo.c_str());

            }

            vector<ProdutoRanqueado> recomendados = RecomendarProdutos(lista, matriz, indice_cliente, 3);
            
        } else {
            printf("\nCliente %s nao encontrado.\n", cliente_alvo.c_str());
        }

    }

    return 0;
}