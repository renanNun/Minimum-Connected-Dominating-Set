#ifndef NO_H
#define NO_H

#include <iostream>
#include "Aresta.h"

using namespace std;


/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 2.0
*/
class No
{
public:
    No(int id);
    No(int id, int peso);
    virtual ~No();

    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();
    int getId();
    int getGrauEntrada();
    int getGrauSaida();
    int getPeso();
    No* getProx();

    void setProxNo(No* no);
    void setPeso(int peso);

    bool existeAresta(int id_alvo);
    void inserirAresta(int id_alvo,int peso);
    void removerTodasArestas();
    int removerAresta(int id, bool direcionado, No* no_alvo);
    Aresta* getArestaEntre(int id_alvo);
    bool existeArestaEntre(int id_alvo);

    void aumentaGrauEntrada();
    void aumentaGrauSaida();
    void diminuiGrauEntrada();
    void diminuiGrauSaida();

    //Variável para DFS e BFS
    int getI();
    void setI(int i);


private:
    int id; // identificador do No
    Aresta* primeira_aresta; // Ponteiro para a primeira aresta do Nó
    Aresta* ultima_aresta; // Ponteiro para a ultima aresta  do Nó
    int grau_de_entrada; // Inteiro que guarda o grau de entrada de Nós direcionados
    int grau_de_saida; // Inteiro que guarda o grau de saida de Nós direcionados
    int peso;  // Inteiro que guarda o peso de Nós ponderados
    No* prox; //ponteiro para o proximo Nó

    int iterador; // inteiro para auxiliar nas funções busca em largura e busca em profundidade
};

#endif // NO_H
