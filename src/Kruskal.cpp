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
    pais();


    for(Aresta* & arestaAux : listaArestas)
    {

        if(!ehCiclo(arestaAux))
        {
            grafoKruskal.inserirAresta(arestaAux->getId_Origem(),arestaAux->getId_Alvo(),arestaAux->getPeso());
        } else {
        }
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

// Union find

void Kruskal::pais()
{
    for (No * i = grafo->getPrimeiroNo() ; i!=nullptr; i=i->getProx())
    {
            i->setPai(i->getId());
    }
}

No *  Kruskal::acha(No * u)
{
    No * z = this->grafo->getNo(u->getPai());

    if(z == u)
    {
       return z;
    } else {
        return acha(z);
    }
    //return z;
}

void Kruskal::une(No *x, No *y)
{

    No * xraiz = acha(x);
    No * yraiz = acha(y);

    xraiz->setPai(yraiz->getId());

}


bool Kruskal::ehCiclo(Aresta * a)
{

    No * aux1 = grafoKruskal.getNo(a->getId_Origem());
    No * aux2 =  grafoKruskal.getNo(a->getId_Alvo());

    if(acha(aux1) == acha(aux2))
    {
        return true;
    }
    else
    {
        une(aux1,aux2);
    }
    return false;

}




