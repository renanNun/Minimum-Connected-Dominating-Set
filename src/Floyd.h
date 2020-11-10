#ifndef FLOYD_H
#define FLOYD_H

#include "Grafo.h"
#include <fstream>

using namespace std;

class Floyd
{

public:
    Floyd(Grafo* grafo);
    ~Floyd();

    void floydWarshall();
    void imprimeSolucao();
    void imprimeSolucaoFile(fstream &outputFile);

private:
    int** pesoArestas;
    int** distanciaArestas;
    int n;

    void iniciaMatrizes(Grafo* grafo);
};

#endif // FLOYD_H
