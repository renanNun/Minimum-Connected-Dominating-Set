#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Grafo.h"

using namespace std;

class Kruskal
{
    public:
        Kruskal(Grafo* grafo);
        virtual ~Kruskal();

        void algoritmo();
        void imprime();

    private:
        Grafo* grafo;
        int* vertices;
        int n;
        Aresta** mst;

        No** ch;
        int sz[];

        void iniciaI();
        void quickSort(Aresta* vetor[],int inicio,int fim);
        void UFinit();
        No* UFind(int v);
        void UFuinion(No* v0, No* w0);
};

#endif // KRUSKAL_H
