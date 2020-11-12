#ifndef FLOYD_H
#define FLOYD_H

#include "Grafo.h"
#include <fstream>

using namespace std;

/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 1.0
*/

class Floyd
{

public:
    Floyd(Grafo* grafo);
    ~Floyd();

    void floydWarshall();
    void imprimeSolucao();
    void imprimeSolucaoFile(fstream &outputFile);

private:
    int** pesoArestas; // Matriz de peso das Arestas
    int** distanciaArestas; // Matriz das distancias das arestas
    int n; // Ordem da matriz

    void iniciaMatrizes(Grafo* grafo);
};

#endif // FLOYD_H
