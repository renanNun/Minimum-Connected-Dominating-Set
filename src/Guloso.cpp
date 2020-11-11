#include "Guloso.h"



Guloso::Guloso(Grafo* grafo)
{
    this->grafo=grafo;
}

Guloso::~Guloso()
{

}

void Guloso::gerar()
{
    preencheGrafo();
    preencheListaArestas();
    Aresta * arestaAux;


    for(Aresta * & arestaAux :listaAresta)
    {

    }






}


void Guloso::preencheListaArestas()
{
    int idAresta=0;
    list <Aresta *> listaAresta;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas
    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i = grafoGuloso->getPrimeiroNo(); i!=nullptr; i=i->getProx())
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


}

void Guloso::preencheGrafo()
{

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        grafoGuloso.inserirNo(i->getId());
    }

    int idAresta=0;
    list <Aresta *> listaAresta;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas
    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i = grafo->getPrimeiroNo(); i!=nullptr; i=i->getProx())
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

    for(Aresta* & arestaAux : listaArestasAux)
    {
        this->grafoGuloso.inserirAresta(arestaAux->getId_Origem(), arestaAux->getId_Alvo(),arestaAux->getPeso());
    }
}
