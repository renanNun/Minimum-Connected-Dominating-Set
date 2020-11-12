#ifndef PRIM_H
#define PRIM_H

#include "Grafo.h"
#include <list>

using namespace std;


/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 1.0
*/

class Prim
{

public:
    Prim(Grafo* grafo, int no_escolhido); // Construtor
    ~Prim(); // Destrutor
    void imprime(); // Função para imprimir a solução
    void imprimeFile(fstream &outputFile); // função para salvar a solução em um arquivo de saida
    void algoritmoDePrim(); // Algoritmo da solução

private:

    Grafo* grafo; // Armazena o ponteiro do Grafo pasado pelo usuario
    No* noEscolhido; // No escolhido pelo usuario
    list<Aresta*> arestasArvore; //List que armazena os ponteiros para a solução



};

#endif // PRIM_H
