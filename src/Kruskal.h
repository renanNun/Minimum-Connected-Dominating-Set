#ifndef GRAFO_KRUSKAL_H
#define GRAFO_KRUSKAL_H

#include <iostream>

#include "Grafo.h"
#include <list>




using namespace std;

class Kruskal
{

public:
    Kruskal(Grafo *grafo);
    ~Kruskal();

    void imprimeFile(fstream &outputFile);

private:
    Grafo *grafo;
    bool direcional;
    int ordem;
    int m;
    No * noInicial;
    void preencheListaArestas();
    list<Aresta*> listaArestas;



};


#endif //GRAFO_KRUSKAL_H
