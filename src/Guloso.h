#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"
#include <time.h>
#include <math.h>

class Guloso
{
public:
    Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo.
    virtual ~Guloso();

    void subconjuntoDominanteMinimoConexo();
private:
    int* solucao;
    Grafo * grafo;
    void algoritmoGuloso();
    void algoritmoGulosoRandomizado();

    int gerarSemente();
    void quickSort(int vetor[],int esquerda,int direita, int* indices);
};

#endif // GULOSO_H
