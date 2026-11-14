#include "leitura.h"
#include "similaridade.h"
#include <iostream>

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
            printf("\nCliente: %s \nProdutos (IDs):\n", cliente_alvo.c_str());

            if (resultado.indiceCliente != -1){
                printf("O cliente mais similar (indice): %d | Distancia: %.3f\n", resultado.indiceCliente, resultado.valor);
            } else {
                printf ("Nao ha' outro cliente para comparar\n");
            }

            vector<int> produtos = lista.prod_clientes[indice_cliente];
            for (int id_prod : produtos) {
                int codigo_prod_original = lista.cod_produtos[id_prod];
                printf("  - ID Produto: %d\n", codigo_prod_original);
            }
        } else {
            printf("\nCliente %s nao encontrado.\n", cliente_alvo.c_str());
        }
    }

    return 0;
}