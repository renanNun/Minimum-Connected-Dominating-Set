#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"

class Guloso
{
    public:
        Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo.
        virtual ~Guloso();
        void imprime();

    private:
        Grafo * grafo;
        Grafo grafoGuloso;
        void preencheGrafo();
        void algoritmoGuloso();

        void coloreDeBranco();
        void quickSort(int vetor[],int esquerda,int direita, int* indices);
};

#endif // GULOSO_H
