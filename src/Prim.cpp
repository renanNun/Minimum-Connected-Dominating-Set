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
    //gerar();
    algoritmoDePrim();
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
            if(arestaAux->getId_Origem() == menorPeso->getId() || arestaAux->getId_Alvo() == menorPeso->getId() )
            {
                if(arestaAux->getId_Origem() == menorPeso->getId())
                {
                    if(grafo->getNo(arestaAux->getId_Alvo())->getPesoEspecial() >= arestaAux->getPeso())
                    {
                        grafo->getNo(arestaAux->getId_Alvo())->setPesoEspecial(arestaAux->getPeso());
                    }
                }
                else
                {
                    if(grafo->getNo(arestaAux->getId_Origem())->getPesoEspecial() >= arestaAux->getPeso())
                    {
                        grafo->getNo(arestaAux->getId_Origem())->setPesoEspecial(arestaAux->getPeso());
                    }
                }
            }
        }
        listaNos.sort(ListaNoComparator());


        if(listaNosColocados.size() > 0)
        {
            Aresta * aux2;
            No * aux3 = listaNosColocados.back();
            aux2 = menorPeso->getArestaEntre(aux3->getId());
            if(aux3 == menorPeso)
            {
                cout<< "ERRO" <<endl;
            }
            if(aux2 != nullptr)
            {
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
                cout<< "erro"<<endl;
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

//Implementação do Renan
void Prim::algoritmoDePrim()
{
    list<Aresta*> arestasArvore;
    int menorPeso;
    int verticesVisitados = 0;

    bool flagA = true; //primeiro teste do algoritmo de prim
    int* verticesDoGrafo = new int[grafo->getOrdem()];
    int* indices = new int[grafo->getOrdem()];
    No* no = grafo->getPrimeiroNo();
    No* aux;
    Aresta* arestaMenorPeso = no->getPrimeiraAresta();

    menorPeso = arestaMenorPeso->getPeso();
    Aresta* a;

    for(int i = 0; i < grafo->getOrdem() && no != nullptr; i++)
    {
        no->setI(i);
        verticesDoGrafo[i] = 0;
        indices[i] = no->getId();
        no = no->getProx();
    }

    no = noEscolhido;

    while(no != nullptr)
    {
        a = no->getPrimeiraAresta();

        while(a != nullptr)
        {
            if(a->getPeso() < menorPeso)
            {
                arestaMenorPeso = a;
                menorPeso = a->getPeso();
            }
            a = a->getProxAresta();
        }
        no = no->getProx();
    }

    arestasArvore.push_back(arestaMenorPeso);
    aux = grafo->getNo(arestaMenorPeso->getId_Alvo());
    verticesDoGrafo[aux->getI()] = 1;
    verticesVisitados++;

    aux = grafo->getNo(arestaMenorPeso->getId_Origem());
    verticesDoGrafo[aux->getI()] = 1;
    verticesVisitados++;

    while(verticesVisitados < grafo->getOrdem())
    {
        flagA = true;
        arestaMenorPeso = nullptr;
        for(int i = 0; i < grafo->getOrdem(); i++)
        {
            if(verticesDoGrafo[i] == 1)
            {
                a = grafo->getNo(indices[i])->getPrimeiraAresta();

                while(a != nullptr)
                {
                    aux = grafo->getNo(a->getId_Alvo());
                    if(verticesDoGrafo[aux->getI()] != 1)
                    {
                        if(flagA)
                        {
                            arestaMenorPeso = a;
                            menorPeso = a->getPeso();
                            flagA = false;
                        } else {
                            if(a->getPeso() < menorPeso)
                            {
                                arestaMenorPeso = a;
                                menorPeso = a->getPeso();
                            }
                        }
                    }
                    a = a->getProxAresta();
                }
            }
        }
        if(arestaMenorPeso == nullptr)
            break;
        arestasArvore.push_back(arestaMenorPeso);
        aux = grafo->getNo(arestaMenorPeso->getId_Alvo());
        verticesDoGrafo[aux->getI()] = 1;
        verticesVisitados++;
    }
    cout << "PRIM" << endl;
    for(Aresta* & arestaAux : arestasArvore)
    {
        cout << arestaAux->getId_Origem() << "-->" << arestaAux->getId_Alvo() << " " << arestaAux->getPeso() << endl;
    }
    cout << endl;
}
