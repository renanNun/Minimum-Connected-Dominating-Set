#ifndef GRAFO_KRUSKAL_H
#define GRAFO_KRUSKAL_H

#include <iostream>

#include "Grafo.h"




using namespace std;

class Kruskal
{

public:
    Kruskal(Grafo *grafo);
    ~Kruskal();

      Grafo* gerar(float *soma);

private:
    Grafo *grafo;
    bool direcional;
    int ordem;
    int m;
    No *listaNos;

    void vetorIdNos(int* idNos);

    int encontraIndice(int *idNos, int id);

    // Fun��o auxiliar que realiza a troca de posi��es entre valores dos vetores passados como par�metro.
    void troca(float *pesos, Aresta *conj, int i, int j);

    // Fun��o auxiliar que retorna o �ndice da parti��o do QuickSort. Utiliza-se como piv� a �ltima posi��o do vetor.
    int particao(float *pesos, Aresta *conj, int inicio, int fim);

    // Fun��o recursiva que implementa um QuickSort para fazer a ordena��o dos vetores passados como par�metro.
    void ordenaVetor(float *pesos, Aresta *conj, int inicio, int fim);


    // Função usada para encontrar o conjunto de arestas da arvore geradora mínima de um grafo.
    // Retorna a soma dos pesos das arestas desse conjunto.
    float auxKruskal(Aresta *arestasAGM);




    // Função que retorna o subgrafo correspondente a arvore geradora mínima do grafo.

};


#endif //GRAFO_KRUSKAL_H
