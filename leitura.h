#ifndef leitura_h
#define leitura_h

#include <vector>
#include <iostream>
#include <map>
using namespace std;

typedef struct {
    char data[9];
    char cliente[20];
    int produto;
    char nome[200];
} Dados; 

typedef struct {
    vector <string> cod_clientes;
    map <string, int> map_clientes;
    vector <int> cod_produtos;
    map <int, int> map_produtos;
    vector <vector <int>> prod_clientes;
} ListaCompras;

int leitura(int argc, char *argv[], ListaCompras &lista);


#endif