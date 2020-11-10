#ifndef PRIM_H
#define PRIM_H

#include "Grafo.h"
#include <list>

using namespace std;

class Prim
{

public:
    Prim(Grafo* grafo, int no_escolhido);
    ~Prim();
    Grafo gerar();
private:
    Grafo* grafo;
    Grafo grafoPrim;
    int n;
    list<Aresta*> listaArestas;
    No* noEscolhido;

    void preencheListaArestas(No* noInicial);
    void preencheListaNos(No* noInicial);

/*public:
    Prim(Grafo *grafo);
    ~Prim();
    Grafo *gerar(int *soma);


private:
    Grafo *grafo;
    void ordenar(Aresta **a,int n);
    int binarySearch(Aresta **a, Aresta *item, int low, int high);
    Aresta** prim();*/
};

#endif // PRIM_H
