#include "leitura.h"
#include <stdio.h>
#include "similaridade.h"

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

    char codigo_cliente_input[20];
    printf("\nDigite o codigo do cliente: ");
    scanf("%19s", codigo_cliente_input);
    string cliente_alvo = codigo_cliente_input;

    if (lista.map_clientes.find(cliente_alvo) != lista.map_clientes.end()) {
        int indice_cliente = lista.map_clientes[cliente_alvo];
        ResultadoBusca resultado = buscarMaisSimilar(matriz, indice_cliente);
        if (resultado.indiceCliente != -1){
            printf("O cliente mais similar (indice): %d | Distancia: %.3f\n", resultado.indiceCliente, resultado.valor);
        } else {
            printf ("Nao ha' outro cliente para comparar\n");
            }
        }
    
    liberarMatrizes(matriz);

    return 0;
}