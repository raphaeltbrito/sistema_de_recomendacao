#include "leitura.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    ListaCompras lista;

    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    printf("Clientes: %d\n", (int)lista.cod_clientes.size());  
    printf("Produtos: %d\n", (int)lista.cod_produtos.size());

    for (int i = 0; i < 3; i++) {
        char codigo_cliente_input[20];
        printf("\nDigite o codigo do cliente %d de 3: ", i + 1);
        scanf("%19s", codigo_cliente_input);
        string cliente_alvo = codigo_cliente_input;

        if (lista.map_clientes.find(cliente_alvo) != lista.map_clientes.end()) {
            int indice_cliente = lista.map_clientes[cliente_alvo];
            printf("====PRODUTOS COMPRADOS====\n");
            
            vector<int> produtos = lista.prod_clientes[indice_cliente];
            for (int id_prod : produtos) {
                string nome_externo = lista.nome_produtos[id_prod];
                printf("  Produto Comprado: %s\n", nome_externo.c_str());
            }
        } else {
            printf("codigo invalido\n");
        }
    }

    return 0;

}