#include "Kruskal.h"
#define INFINITO 99999

Kruskal::Kruskal(Grafo* grafo)
{
    this->grafo = grafo;
    this->n = grafo->getOrdem();
    this->vertices = new int[n];

    ch = new No*[n];
    this->sz[n];

    algoritmo();
}

Kruskal::~Kruskal()
{
    delete [] vertices;
}

void Kruskal::algoritmo()
{
    Aresta* aresta[n];

    int i = 0;
    for(No* no = this->grafo->getPrimeiroNo(); no != nullptr; no = no->getProx())
    {
        for(Aresta* a = no->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
            if(no->getId() < a->getId_Alvo())
                aresta[i++] = new Aresta(a->getId_Alvo(),no->getId(),a->getPeso());
    }

    int e = grafo->getNumeroArestas()/2;
    quickSort(aresta,0,e-1);
    iniciaI();
    UFinit();

    int k = 0;
    for(int i = 0; k < n-1; i++)
    {
        No* v0 = UFind(aresta[i]->getId_Alvo());
        No* w0 = UFind(aresta[i]->getId_Origem());
        if(v0 != w0)
        {
            UFuinion(v0,w0);
            mst[k++] = aresta[i];
        }
    }

    for(int i = 0; i < n; i++)
    {
        cout << mst[i]->getPeso() << " " << endl;
    }
}

void Kruskal::quickSort(Aresta* vetor[],int inicio,int fim)
{
    int i,j;
    Aresta* pivo;
    i = inicio;
    j = fim;
    int ind = (rand() % (fim - inicio + 1)) + inicio;
    pivo = vetor[ind];

    while(i < j)
    {
        while(vetor[i]->getPeso() < pivo->getPeso() && i < fim)
            i++;
        while(vetor[j]->getPeso() > pivo->getPeso() && j > inicio)
            j--;

        if(i <= j)
        {
            swap(vetor[i],vetor[j]);
            i++;
            j--;
        }
    }

    if(j > inicio)
        quickSort(vetor,inicio,j);
    if(i < fim)
        quickSort(vetor,i,fim);
}

void Kruskal::iniciaI()
{
    No* no = grafo->getPrimeiroNo();
    for(int i = 0; i < n; i++)
    {
        no->setI(i);
        no = no->getProx();
    }
}

void Kruskal::UFinit()
{
    //cout << "HERE" << endl;
    //int cont = n;
    for(No* no = this->grafo->getPrimeiroNo(); no != nullptr; no = no->getProx())
    {
        ch[no->getI()] = no;
        sz[no->getI()] = 1;
        //cout << "contador " << cont << " ";
        //cont --;
    }
}

No* Kruskal::UFind(int v)
{
   // cout << "BUSCANDO" << endl;
    No* v0 = grafo->getNo(v);
    while(v0 != ch[v0->getI()])
        v0 = ch[v0->getI()];
    return v0;
}

void Kruskal::UFuinion(No* v0,No* w0)
{
    if(sz[v0->getI()] < sz[w0->getI()])
    {
        ch[v0->getI()] = w0;
        sz[w0->getI()] += sz[w0->getI()];
    } else {
        ch[w0->getI()] = v0;
        sz[v0->getI()] += sz[w0->getI()];
    }
}
