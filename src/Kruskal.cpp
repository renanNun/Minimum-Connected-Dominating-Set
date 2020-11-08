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

    algoritmo();
}
Kruskal:: ~Kruskal() {}

void Kruskal::algoritmo()
{

    preencheListaArestas();
    preencheListaNos();

    No * noAux;
   /* for(Aresta* & arestaAux : listaArestas)
    {
        grafoKruskal.inserirAresta(arestaAux->getId_Origem(),arestaAux->getId_Alvo(),arestaAux->getPeso());
        if(grafoKruskal.ehCiclo())
        {
            No * i= grafoKruskal.getNo(arestaAux->getId_Origem());
            i->removerAresta(arestaAux->getId_Origem(),false, grafoKruskal.getNo(arestaAux->getId_Alvo()));
            i = grafoKruskal.getNo(arestaAux->getId_Alvo());
            i->removerAresta(arestaAux->getId_Alvo(),false, grafoKruskal.getNo(arestaAux->getId_Origem()));
        }
    }*/

    for(Aresta* & arestaAux : listaArestas)
    {

    }


imprime();
}



void Kruskal::preencheListaArestas()
{

    int idAresta=0;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas

    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        for(Aresta* j= i->getPrimeiraAresta(); j!=nullptr; j=j->getProxAresta())
        {
            j->setIdAresta(idAresta);
            idAresta++;
            listaArestasAux.push_back(j);
        }
    }

    // Insere na lista final elementos que não se repetem (devido a implementação da aresta)
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

    // Ordena lista de arestas em função do peso
    listaArestas.sort(ListaArestaComparator());
}

void Kruskal::preencheListaNos()
{

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        grafoKruskal.inserirNo(i->getId());

    }

}

void Kruskal::imprimeFile(fstream &outputFile)
{
   outputFile<< grafoKruskal.imprimir();
}

void Kruskal::imprime()
{
    cout<<grafoKruskal.imprimir();
}



