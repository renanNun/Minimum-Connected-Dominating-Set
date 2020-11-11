#ifndef GULOSO_H
#define GULOSO_H
#include "Grafo.h"

class Guloso
{
    public:
        Guloso(Grafo* grafo); //Subconjunto dominante mínimo conexo.
        virtual ~Guloso();
        void imprime();

    private:
        Grafo * grafo;
        list <Aresta *> listaAresta;
        void preencheListaArestas();
        Grafo grafoGuloso;
        void preencheGrafo();
        void gerar();


};

#endif // GULOSO_H
