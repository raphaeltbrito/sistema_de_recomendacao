#include "leitura.h"
#include <iostream>

int main(int argc, char *argv[]) {
    ListaCompras lista;

    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    string clientes_teste[3] = {"99CL9Y01", "9O6OSM01", "99EF7201"};

    for (int i = 0; i < 3; i++) {
        string cliente_alvo = clientes_teste[i];

        if (lista.map_clientes.find(cliente_alvo) != lista.map_clientes.end()) {
            int indice_cliente = lista.map_clientes[cliente_alvo];
            printf("\nCliente: %s \nProdutos (IDs):\n", cliente_alvo.c_str());

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