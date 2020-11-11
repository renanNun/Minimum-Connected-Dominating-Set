#include "Guloso.h"

/*
* Cores para coloração
* branco = 0
* cinza = 1
* preto = 2
*/

Guloso::Guloso(Grafo* grafo)
{
    this->grafo=grafo;
    algoritmoGuloso();
    //cout << grafoGuloso.imprimir();
}

Guloso::~Guloso()
{

}

void Guloso::algoritmoGuloso()
{
    preencheGrafo(); //Copia o Grafo original
    coloreDeBranco(); //Todos os nós do Grafo são pintados de Branco

    int* listaGraus = new int[grafoGuloso.getOrdem()];
    int* listaIds = new int[grafoGuloso.getOrdem()];

    int i = 0;
    for(No* no = grafoGuloso.getPrimeiroNo(); no != nullptr; no = no->getProx()) //Iniciando graus e ids
    {
        listaGraus[i] = no->getGrauEntrada();
        listaIds[i] = no->getId();
        i++;
    }

    quickSort(listaGraus,0,grafoGuloso.getOrdem()-1,listaIds); //Ordenando do maior para o menor grau

    No* no = grafoGuloso.getNo(listaIds[0]);
    No* aux;
    bool w = 1;

    while(w)
    {
        no->setI(2); //Pinta o Grafo de preto

        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            aux = grafoGuloso.getNo(aresta->getId_Alvo());
            aux->setI(1); //Os Adjacentes a ele se tornam cinzas
        }

        if()
        {

        } else {
            w = false;
        }
    }

}

void Guloso::quickSort(int* vetor,int esquerda,int direita, int* indices)
{
    int i,j,x;
    i = esquerda;
    j = direita;
    int ind = (rand() % (direita - esquerda + 1))+esquerda;
    x = vetor[ind];

    while(i < j)
    {
        while(vetor[i] > x && i < direita)
            i++;
        while(vetor[j] < x && j > esquerda)
            j--;

        if(i <= j)
        {
            if(indices != nullptr)
            {
                swap(indices[i],indices[j]);
            }
            swap(vetor[i],vetor[j]);
            i++;
            j--;
        }
    }

    if(j > esquerda)
        quickSort(vetor,esquerda,j,indices);
    if(i < direita)
        quickSort(vetor,i,direita,indices);
}

void Guloso::imprime()
{
    cout<<grafoGuloso.imprimir();
}

void Guloso::preencheGrafo()
{
    int ordem = 0;
    int idAresta=0;
    list <Aresta *> listaArestas;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas
    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i = grafo->getPrimeiroNo(); i!=nullptr; i=i->getProx())
    {
        grafoGuloso.inserirNo(i->getId());
        ordem++;
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

    grafoGuloso.setOrdem(ordem);
}

void Guloso::coloreDeBranco()
{
    for(No* no = grafoGuloso.getPrimeiroNo(); no != nullptr; no = no->getProx())
    {
        no->setI(0); //Todos os nós são pintados de branco
    }
}
