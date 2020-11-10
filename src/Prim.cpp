#include "Prim.h"
#define INFINITO 999999

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

struct ListaNoComparator
{
    // Compara 2 Arestas usando Peso
    bool operator ()( No* & No1,  No* & No2)
    {
        if(No1->getPesoEspecial() == No2->getPesoEspecial())
            return No1 < No2;
        return No1->getPesoEspecial() < No2->getPesoEspecial();
    }
};




Prim::Prim(Grafo* grafo, int no_escolhido)
{
    this->grafo = grafo;
    noEscolhido = grafo->getNo(no_escolhido);
    gerar();
}

Prim::~Prim()
{

}

void Prim::gerar()
{
    preencheListaArestas();
    preencheListaNos();
    No * noInicial= noEscolhido;
    noInicial->setPesoEspecial(0);
    No * menorPeso;
    list<No *> listaNosColocados;

    cout<<"Tamanho lista de Nos: "<< listaNos.size()<<endl;
    listaNos.sort(ListaNoComparator());

    while(!listaNos.empty())
    {
        menorPeso = listaNos.front();
        listaNos.pop_front();

        grafoPrim.inserirNo(menorPeso->getId());
        menorPeso->Marca();

        for(Aresta* & arestaAux : listaArestas)
        {
            if(arestaAux->getId_Alvo() == menorPeso->getId() || arestaAux->getId_Origem()== menorPeso->getId())
            {
                if(arestaAux->getId_Alvo() == menorPeso->getId())
                {
                    if(grafo->getNo(arestaAux->getId_Alvo())->getPesoEspecial() > arestaAux->getPeso())
                    {
                        grafo->getNo(arestaAux->getId_Origem())->setPesoEspecial(arestaAux->getPeso());
                    }
                }
                else
                {
                    if(grafo->getNo(arestaAux->getId_Origem())->getPesoEspecial() > arestaAux->getPeso())
                    {
                        grafo->getNo(arestaAux->getId_Alvo())->setPesoEspecial(arestaAux->getPeso());
                    }
                }
            }
        }
        listaNos.sort(ListaNoComparator());

        /*for(No* no : listaNos)
        {
            cout << " ID " << no->getId() << " PESO " << no->getPesoEspecial();
        }
        cout << endl;*/

        if(listaNosColocados.size() > 0)
        {
            Aresta * aux2;
            No * aux3 = listaNosColocados.back();
            aux2 = menorPeso->getArestaEntre(aux3->getId());
            if(aux3 == menorPeso)
            {
                cout<<"porra"<<endl;
            }
            if(aux2 != nullptr)
            {
                //cout << "A " << aux2->getId_Origem() << "-->" << aux2->getId_Alvo() << endl;
                grafoPrim.inserirAresta(aux2->getId_Origem(),aux2->getId_Alvo(),aux2->getPeso());
            }
            else
            {
                aux2 = aux3->getArestaEntre(menorPeso->getId());
                if(aux2!=nullptr)
                {
                    grafoPrim.inserirAresta(aux2->getId_Origem(),aux2->getId_Alvo(),aux2->getPeso());
                }
                else
                {
                    cout<< "Deu erro"<<endl;
                }
            }
        }
        if(menorPeso!=nullptr)
        {
            listaNosColocados.push_back(menorPeso);
        }

    }
    cout << "COLOCADOS " << listaNosColocados.size() << endl;
    imprime();
}

void Prim::imprime()
{
    cout<<"imprimindo: "<<endl;

    cout<<grafoPrim.imprimir();

}

void Prim::preencheListaArestas()
{
    int idAresta=0;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas

    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i= grafo->getPrimeiroNo(); i != nullptr; i = i->getProx())
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

void Prim::preencheListaNos()
{
    for (No *i= grafo->getPrimeiroNo(); i != nullptr; i = i->getProx())
    {
        i->desmarca();
        i->setPesoEspecial(9999999);
        listaNos.push_back(i);
    }
}


