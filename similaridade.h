#ifndef similaridade_h
#define similaridade_h
#include "leitura.h"
#include <vector>
using namespace std;

typedef struct {
    vector<vector<int>> compras;
    vector<vector<int>> transposta;
    vector<vector<int>> intersecao;
    vector<vector<double>> similaridade;
} Matrizes;

typedef struct {
   int indiceCliente;
   double valor;
} ResultadoBusca;

void montarMatrizcompras(const ListaCompras &lista, Matrizes &sim);

void montarMatriztransposta(Matrizes &matriz);

void montarMatrizintersecao(Matrizes &matriz);

void montarMatrizsimilaridade(Matrizes &matriz);

ResultadoBusca buscarMaisSimilar(const Matrizes &matriz, int clienteAlvo);

#endif
