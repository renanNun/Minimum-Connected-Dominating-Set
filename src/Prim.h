#ifndef PRIM_H
#define PRIM_H

#include "Grafo.h"

using namespace std;

class Prim
{
public:
    Prim(Grafo *grafo);
    ~Prim();
    Grafo *gerar(int *soma);


private:
    Grafo *grafo;
    void ordenar(Aresta **a,int n);
    int binarySearch(Aresta **a, Aresta *item, int low, int high);
    Aresta** prim();
};

#endif // PRIM_H
