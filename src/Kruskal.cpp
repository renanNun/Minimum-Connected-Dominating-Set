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
    list<Aresta*> listaArestasaux;
    Aresta * arestaAux;
    Aresta * arestaAux2;
    int contador=0;
    int idAresta=0;

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        for(Aresta* j= i->getPrimeiraAresta(); j!=nullptr; j=j->getProxAresta())
        {
            j->setIdAresta(idAresta);
            idAresta++;
            listaArestasaux.push_back(j);
        }
    }

    // cout<< "Lista Inicial: " << listaArestasaux.size() <<endl;
    /*for(Aresta* & aresta : listaArestasaux)
        cout<<aresta->getPeso()<<endl;*/

    while(!listaArestasaux.empty())
    {
        arestaAux=listaArestasaux.front();
        listaArestasaux.pop_front();
        contador=0;

        if(!listaArestas.empty())
        {
            list <Aresta *>listaArestasaux2(listaArestas);
            for (Aresta* & arestAux2 : listaArestasaux)
            {
                if(!listaArestasaux2.empty())
                {
                    contador++;
                    arestaAux2=listaArestasaux2.front();
                    listaArestasaux2.pop_front();

                    if(arestaAux2->getId_Alvo() == arestaAux->getId_Origem()
                            && arestaAux2->getId_Origem() ==arestaAux->getId_Alvo() )
                    {
                        arestaAux= nullptr;
                        break;
                    }
                    if(contador==listaArestas.size())
                    {
                        listaArestas.push_back(arestaAux);
                    }


                }
            }

        }
        else
            listaArestas.push_back(arestaAux);

    }
    listaArestas.sort(ListaArestaComparator());
    cout<< "Lista Final: " << listaArestas.size() <<endl;
    /*for(Aresta* & aresta : listaArestas)
        cout<<aresta->getIdAresta()<<endl;*/
}


void Kruskal::imprimeFile(fstream &outputFile)
{
    outputFile << "Lista Final: "<<endl;
    for(Aresta* & aresta : listaArestas)
        outputFile<<aresta->getIdAresta()<<endl;
}

