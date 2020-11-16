#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"
#include <chrono>
#include <math.h>

class Guloso
{
public:
    Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo.
    virtual ~Guloso();

    void imprime(fstream &outputFile);
private:
    int* solucao;
    Grafo * grafo;
    void algoritmoGuloso();
    void algoritmoGulosoRandomizado();

    int gerarSemente();
    void quickSort(int vetor[],int esquerda,int direita, int* indices,int* coloracao);
    std::chrono::time_point<std::chrono::system_clock> start, end;
};

#endif // GULOSO_H
