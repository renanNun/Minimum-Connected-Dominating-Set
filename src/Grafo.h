#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include "No.h"
#include "Aresta.h"

using namespace std;

/**
*   Universidade Federal de Juiz de Fora
*   Criador: Renan Nunes da Costa Gonçalves e Luan Reis Ciribelli
*   versão: 2.0
*/
class Grafo{
    
    public:
        Grafo();
        Grafo(int ordem);
        Grafo(int ordem, bool direcionado,bool ponderado_aresta,bool ponderado_no);
        virtual ~Grafo();

        int getOrdem();
        int getNumeroArestas();
        bool getDirecionado();
        bool getPonderadoAresta();
        bool getPonderadoNo();

        No* getPrimeiroNo();
        No* getUltimoNo();

        void setOrdem(int ordem);
        void setNumeroArestas(int numeroArestas);
        void aumentaNumArestas();
        void diminuiNumArestas();

        /*Funções do Grafo*/
        No* getNo(int id);
        bool existeNo(int id);
        void inserirNo(int id);
        void removerNo(int id);
        void inserirAresta(int id,int id_alvo,int peso);
    private:
        int ordem;
        int numero_arestas;
        bool direcionado,ponderado_no,ponderado_aresta;
        No* primeiro_no;
        No* ultimo_no;

        int** matriz_pesos;
        bool** matriz_adjacencia;

};

#endif // GRAFO_H