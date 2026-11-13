#include "leitura.h"
#include <stdio.h>
#include <string>
using namespace std;


int leitura(int argc, char *argv[]) {
    // Verifica se o nome do arquivo foi informado.
    if (argc != 2) {
        printf("Uso: %s <arquivo.csv>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    ListaCompras lista;
    Dados d;

    // Descarta o cabeçalho sem armazená-lo.
    fscanf(arquivo, "%*[^\n]");


    int colunas_lidas;
    while ((colunas_lidas = fscanf(arquivo, " %8[^,],%19[^,],%d,%199[^\r\n]", d.data, d.cliente, &d.produto, d.nome)) != EOF){
        if (colunas_lidas != 4){
            continue;
        }

        string codigo_externo_cliente = d.cliente;
        int codigo_externo_produto = d.produto;

        int indice_clientes;
        if (lista.map_clientes.find(codigo_externo_cliente) == lista.map_clientes.end()) {
            indice_clientes = lista.cod_clientes.size();
            lista.cod_clientes.push_back(codigo_externo_cliente);
            lista.map_clientes[codigo_externo_cliente] = indice_clientes;

            lista.prod_clientes.push_back(vector<int>());        
        } else {
            indice_clientes = lista.map_clientes[codigo_externo_cliente];
        }

        int indice_produtos;
        if (lista.map_produtos.find(codigo_externo_produto) == lista.map_produtos.end()){
            indice_produtos = lista.cod_produtos.size();
            lista.cod_produtos.push_back(codigo_externo_produto);
            lista.map_produtos[codigo_externo_produto] = indice_produtos;
        } else {
            indice_produtos = lista.map_produtos[codigo_externo_produto];
        }

        lista.prod_clientes[indice_clientes].push_back(indice_produtos);

        printf("Data: %s | Cliente: %s | Produto: %d | Nome: %s\n",
               d.data, d.cliente, d.produto, d.nome);
    }

    printf("Clientes: %d\n", (int)lista.cod_clientes.size());  
    printf("Produtos: %d\n", (int)lista.cod_produtos.size()); 

    fclose(arquivo);

    return 0;
}