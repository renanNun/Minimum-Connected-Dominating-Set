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
    list<Aresta* >  listaArestasAux;

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        for(Aresta* j= i->getPrimeiraAresta(); j!=nullptr; j=j->getProxAresta())
        {
            j->setIdAresta(idAresta);
            idAresta++;
            listaArestasAux.push_back(j);
        }
    }

    cout<< "Lista Inicial: " << listaArestasAux.size() <<endl;


    // Retirar elementos iguais
 //   listaArestas.push_front(listaArestasAux.front());
    int contador;
    for(Aresta* & arestaAux : listaArestasAux)
    {
        contador=0;
        for(Aresta* & arestaAux2 : listaArestas)
        {
            if(arestaAux2->getId_Alvo() == arestaAux->getId_Origem()
                 &&   arestaAux2->getId_Origem() == arestaAux->getId_Alvo())
                break;
            else
                contador++;
        }
        if(contador == listaArestas.size())
            listaArestas.push_front(arestaAux);
    }



    listaArestas.sort(ListaArestaComparator());

    cout<< "Lista Final: " << listaArestas.size() <<endl;


        for(Aresta* & aresta : listaArestas)
             cout<<aresta->getPeso()<<endl;

}



void Kruskal::imprimeFile(fstream &outputFile)
{
    outputFile << "Lista Final: "<<endl;
    for(Aresta* & aresta : listaArestas)
        outputFile<<aresta->getPeso()<<endl;
}

