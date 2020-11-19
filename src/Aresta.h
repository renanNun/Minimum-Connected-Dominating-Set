#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

using namespace std;

/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 2.0
*/
class Aresta
{

public:
    Aresta();
    Aresta(int id_alvo);
    Aresta(int id_alvo, int peso);
    Aresta(int id_alvo, int id_origem, int peso);

    virtual ~Aresta();

    int getId_Alvo();
    int getId_Origem();
    int getPeso();
    Aresta* getProxAresta();

    void setProxAresta(Aresta* aresta);
    void setPeso(int peso);
    void setId_Origem(int novo_id_origem);
    void setId_alvo(int novo_id_alvo);
    
   // Função especial que serve para estrtura de comparação do Kruskal
    bool operator <(const Aresta & ArestaObj) const
    {
        return peso < ArestaObj.peso;
    }


private:
    int id_alvo; // Identificiador do id do Nó adjacente
    int id_origem; // Identificiador do id do Nó de origem
    int peso; // peso da aresta ponderada
    Aresta* prox; // Ponteiro para a proxima aresta
    
};

#endif // ARESTA_H
