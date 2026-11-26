#include "leitura.h"
#include <stdio.h>
#include "similaridade.h"
#include "recomendacao.h"

int main(int argc, char *argv[]){
    ListaCompras lista;
    Matrizes matriz = {};

    if (leitura(argc, argv, lista) != 0) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    montarMatrizcompras(lista, matriz);
    montarMatriztransposta(matriz);
    montarMatrizintersecao(matriz);
    montarMatrizsimilaridade(matriz);

    if (matriz.similaridade == NULL){
        printf("Não foi possível construir as matrizes !!");
        liberarMatrizes(matriz);
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        char codigo_cliente_input[20];
        printf("\nDigite o codigo do cliente %d de 3: ", i + 1);
        scanf("%19s", codigo_cliente_input);
        string cliente_alvo = codigo_cliente_input;

        if (lista.map_clientes.find(cliente_alvo) != lista.map_clientes.end()) {
            int indice_cliente = lista.map_clientes[cliente_alvo];

            printf("====PRODUTOS RECOMENDADOS====\n");
            vector<ProdutoRanqueado> recomendados = RecomendarProdutos(lista, matriz, indice_cliente, 3);

            if (recomendados.size() == 0) {
                printf("Nenhum produto disponivel para recomendacao\n");
            }

            for(int j = 0; j < recomendados.size(); j++){
                int produto = recomendados[j].indice_produto_ranking;
                string nome_recomendado = lista.nome_produtos[produto];
                printf("Produto recomendado: %s\n", nome_recomendado.c_str());
            }
            
        } else {
            printf("\nCliente %s nao encontrado.\n", cliente_alvo.c_str());
        }
    }

    liberarMatrizes(matriz);
    return 0;
}