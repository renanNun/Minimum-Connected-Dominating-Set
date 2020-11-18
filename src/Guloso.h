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
    int tamSolucao;
    Grafo * grafo;
    bool verifica;

    /*Algoritmos Gulosos*/
    void algoritmoGuloso();
    void algoritmoGulosoRandomizado();


    /*vetores a serem utilizados*/
    int* solucao;
    int* listaGraus;
    int* listaIds;
    int* coloracao;
    int* solucaoFinal;

    void quickSort(int vetor[],int esquerda,int direita, int* indices,int* coloracao);

    /*Variáveis para o calculo de tempo*/
    std::chrono::time_point<std::chrono::system_clock> init, end;
    std::chrono::duration<double> elapsed_seconds;
    double duracao;

    /*Funções auxiliares*/
    void start();
    void finish();
    void iniciaVetores();
    void resetaSolucaoTemporaria();
    void forcaInicio(int i,int j);

};

#endif // GULOSO_H
