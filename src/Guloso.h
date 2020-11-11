#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"

class Guloso
{
    public:
        Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo.
        virtual ~Guloso();

    private:
        Grafo * grafo;
        void algoritmoGuloso();

        void quickSort(int vetor[],int esquerda,int direita, int* indices);
};

#endif // GULOSO_H
