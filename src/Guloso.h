#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"
#include <chrono>
#include <math.h>


/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 1.0
*/

class Guloso
{
public:
    Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo - Estrategia Gulosa convencional.

    Guloso(Grafo* grafo, double alfa); //Subconjunto dominante mínimo conexo - Estrategia Gulosa randomizada.

    virtual ~Guloso(); // Destrutor

    void imprime(fstream &outputFile); //Função que guarda informação no arquivo passado.


private:
    double alfa; //Alfa para guloso

    int* solucao; // vetor de inteiros que guarda os ids da solução.

    int tamSolucao; // inteiro que guarda tamanho da solução.

    Grafo * grafo; // Ponteiro para armazenar grafo passado pelo usuario

    void algoritmoGuloso();

    void algoritmoGulosoRandomizado();

    bool verifica; //Booleano usado para verificar se a solução encontrada é verdadeira.

    void verificaResposta();

    void quickSort(int vetor[],int esquerda,int direita, int* indices,int* coloracao);

    std::chrono::time_point<std::chrono::system_clock> start, end;

    double duracao; // Double usado para manter controle do tempo da solução.
};

#endif // GULOSO_H
