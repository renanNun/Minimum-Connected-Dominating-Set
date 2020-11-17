#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"
#include <chrono>
#include <math.h>

class Guloso
{
public:
    Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo.
    Guloso(Grafo* grafo, double alfa);
    virtual ~Guloso();

    void imprime(fstream &outputFile);

    void verificaResposta();
private:
    double alfa;
    int* solucao;
    int tamSolucao;
    Grafo * grafo;
    void algoritmoGuloso();
    void algoritmoGulosoRandomizado();
    bool verifica;


    int gerarSemente();
    void quickSort(int vetor[],int esquerda,int direita, int* indices,int* coloracao);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    double duracao;
};

#endif // GULOSO_H
