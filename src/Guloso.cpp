#include "Guloso.h"



Guloso::Guloso(Grafo* grafo)
{
    this->grafo=grafo;
    gerar();
}

Guloso::~Guloso()
{

}

void Guloso::gerar()
{
    preencheGrafo();
    preencheListaArestas();
    Aresta * arestaAux;
    No * noAux;
    arestaAux = listaAresta.front();
    int marcados=0;

    while(marcados <= grafo->getOrdem())
    {
        cout<<"1"<<endl;
        for(Aresta * & arestaAux2 : listaAresta)
        {
            cout<<"2"<<endl;
            if(arestaAux2 != arestaAux &&
                    (arestaAux2->getId_Alvo() ==arestaAux->getId_Alvo() || arestaAux2->getId_Origem() == arestaAux->getId_Alvo() ))
            {
                cout<<"3"<<endl;
                if(arestaAux2->getId_Alvo() ==arestaAux->getId_Alvo())
                {
                    cout<<"4"<<endl;
                    grafoGuloso.removerAresta(arestaAux->getId_Alvo(), arestaAux2->getId_Alvo());
                    arestaAux2->setId_alvo(-1);
                }
                if(arestaAux2->getId_Origem() == arestaAux->getId_Alvo())
                {
                    cout<<"5"<<endl;
                    grafoGuloso.removerAresta(arestaAux->getId_Alvo(), arestaAux2->getId_Origem());
                    arestaAux2->setId_Origem(-1);
                }
            }
        }
        cout<<"6"<<endl;
        noAux=grafoGuloso.getNo(arestaAux->getId_Alvo());
        cout<<"7"<<endl;
        noAux->Marca();
        cout<<"8"<<endl;
        marcados++;
        cout<<"9"<<endl;
        for(Aresta * & arestaAux3 : listaAresta)
        {
            cout<<"10"<<endl;
            if(arestaAux3->getId_Origem() != -1)
            {
                cout<<"11"<<endl;
                arestaAux=arestaAux3;
                break;
            }
        }
    }


    imprime();

}

void Guloso::imprime()
{
    cout<<grafoGuloso.imprimir();
}
void Guloso::preencheListaArestas()
{
    int idAresta=0;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas
    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i = grafoGuloso.getPrimeiroNo(); i!=nullptr; i=i->getProx())
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
        for(Aresta* & arestaAux2 : listaAresta)
        {
            if(arestaAux2->getId_Alvo() == arestaAux->getId_Origem()
                    &&   arestaAux2->getId_Origem() == arestaAux->getId_Alvo())
                break;
            else
                contador++;
        }
        if(contador == listaAresta.size())
            listaAresta.push_front(arestaAux);
    }


}

void Guloso::preencheGrafo()
{
    int idAresta=0;
    list <Aresta *> listaArestas;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas
    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i = grafo->getPrimeiroNo(); i!=nullptr; i=i->getProx())
    {
        grafoGuloso.inserirNo(i->getId());
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
