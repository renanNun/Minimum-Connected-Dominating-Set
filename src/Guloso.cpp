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
    int* solucao = new int[grafo->getOrdem()];
    int* listaGraus = new int[grafo->getOrdem()];
    int* listaIds = new int[grafo->getOrdem()];
    int* coloracao = new int[grafo->getOrdem()];

    //Inicializa toda a solucação com -1
    for(int k = 0; k < grafo->getOrdem(); k++)
        solucao[k] = -1;

    int i = 0;
    for(No* no = grafo->getPrimeiroNo(); no != nullptr; no = no->getProx()) //Iniciando graus e ids
    {
        listaGraus[i] = no->getGrauEntrada();
        listaIds[i] = no->getId();
        coloracao[no->getId()] = 0;
        i++;
    }

    i = 0;
    quickSort(listaGraus,i,grafo->getOrdem()-1,listaIds); //Ordenando do maior para o menor grau

    No* no;
    bool w = 1;
    /*cout << "PRIMEIRA LINHA ";
    for(int t = 0; t < grafo->getOrdem(); t++)
    {
        cout << "\t id " << listaIds[t] << "|" << listaGraus[t] << "|" << coloracao[t];
    }
    cout << endl;*/
    int p,cont;
    while(w)
    {
        no = grafo->getNo(listaIds[i]);
        coloracao[i] = 2; //Pinta o Grafo de preto

        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {

            for(p = 0; p < grafo->getOrdem(); p++)
            {
                if(listaIds[p] == aresta->getId_Alvo())
                    break;
            }

            if(coloracao[aresta->getId_Alvo()] == 0) //Se for branco ok!
            {
                coloracao[aresta->getId_Alvo()] = 1; //Os Adjacentes a ele se tornam cinzas
            }

            if(listaGraus[p] > -1)
                listaGraus[p] = listaGraus[p] - 1; //Diminui o Grau dos já conectados à ele
        }

        if(coloracao[no->getId()] != 1 || coloracao || coloracao[no->getId()] != 0)
        {
            solucao[i] = no->getId();
            i++;
        }


        quickSort(listaGraus,i,grafo->getOrdem()-1, listaIds);

        /*for(int t = 0; t < grafo->getOrdem(); t++)
        {
            cout << "\t id " << listaIds[t] << "|" << listaGraus[t] << "|" << coloracao[t];
        }
        cout << endl;*/
        cont = 0;
        for(int k = 0; k < grafo->getOrdem(); k ++)
        {
            cont++;

            if(coloracao[k] == 0)
            {
                break;
            }
        }

        if(cont == grafo->getOrdem())
            w = false;
    }

    int t = 0;
    cout << endl;
    while(solucao[t] != -1)
    {
        //cout << "Solucao " << solucao[t] << " ";
        t++;
    }
    cout << "Tamanho da solucao " << t << endl;
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
