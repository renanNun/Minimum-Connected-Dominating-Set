#ifndef GRAFO_KRUSKAL_H
#define GRAFO_KRUSKAL_H

#include <iostream>

#include "Grafo.h"
#include <list>


/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 1.0
*/

using namespace std;

class Kruskal
{

public:
    Kruskal(Grafo *grafo); //Construtor
    ~Kruskal(); //Destrutor

    void imprime(); // Função para imprimir a solução
    void imprimeFile(fstream &outputFile); // função para salvar a solução em um arquivo de saida

private:
    Grafo *grafo; // Armazena o ponteiro do Grafo pasado pelo usuario
    Grafo grafoKruskal; // Grafo que será feita a solução
    No * noInicial; // Ponteiro para o primeiro no do Grafo
    list<Aresta*> listaArestas; // Lista de arestas contidas no grafo
    void preencheListaArestas();
    void preencheListaNos();
    void algoritmo();
    int pesoSolucao; //inteiro que armazena o peso de todas as arestas da solução

    // Funções union find

    void pais();
    No* acha(No *u);
    void  une(No *x, No *y);
    bool ehCiclo(Aresta * a);




};


#endif //GRAFO_KRUSKAL_H
