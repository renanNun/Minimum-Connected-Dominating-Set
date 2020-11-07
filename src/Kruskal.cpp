#include "Kruskal.h"
struct ListaArestaComparator
{
    // Compara 2 Arestas usando Peso
    bool operator ()( Aresta* & Aresta1,  Aresta* & Aresta2)
    {
        if(Aresta1->getPeso() == Aresta2->getPeso())
            return Aresta1 < Aresta2;
        return Aresta1->getPeso() < Aresta2->getPeso();
    }
};



Kruskal::Kruskal(Grafo *grafo)
{
    this->grafo = grafo;
    this->ordem = grafo->getOrdem();
    this->m = grafo->getNumeroArestas();
    this->direcional = grafo->getDirecionado();
    this->noInicial = grafo->getPrimeiroNo();

    preencheListaArestas();
}
Kruskal:: ~Kruskal() {}

void Kruskal::preencheListaArestas()
{

    int idAresta=0;

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        for(Aresta* j= i->getPrimeiraAresta(); j!=nullptr; j=j->getProxAresta())
        {
            j->setIdAresta(idAresta);
            idAresta++;
            listaArestas.push_back(j);
        }
    }

    cout<< "Lista Inicial: " << listaArestas.size() <<endl;

    listaArestas.sort(ListaArestaComparator());

    // Retirar elementos iguais




    cout<< "Lista Final: " << listaArestas.size() <<endl;


    /*    for(Aresta* & aresta : listaArestas)
             cout<<aresta->getIdAresta()<<endl;
     */
}



void Kruskal::imprimeFile(fstream &outputFile)
{
    outputFile << "Lista Final: "<<endl;
    for(Aresta* & aresta : listaArestas)
        outputFile<<aresta->getIdAresta()<<endl;
}

