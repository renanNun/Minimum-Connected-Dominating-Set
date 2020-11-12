#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Grafo.h"

using namespace std;

/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 1.0
*/

class Dijkstra
{
public:
    Dijkstra(Grafo* g,int no_inicial);
    virtual ~Dijkstra();

    void iniciaIndices();
    void algoritmo();
    int buscaIndiceComMenorEstimativa(int* distancias, int* abertos,int tam);

    void imprime();
    void imprimeFile(fstream &outputFile);

private:
    Grafo* graph; // Armazena o ponteiro do Grafo pasado pelo usuario
    int no_inicial; // Id do nó inicial


    int* vertices; // vetor de vertices
    int* distancias; // vetor de distancias
    int* predecessores; // vetor de predecessores
    int* abertos; // vetor de abertos
};

#endif // DIJKSTRA_H
