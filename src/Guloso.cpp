#include "Guloso.h"
#define MAX_INTERACOES 1000

/*
* Cores para coloração
* branco = 0
* cinza = 1
* preto = 2
*/

Guloso::Guloso(Grafo* grafo)
{
    this->grafo=grafo;
    solucao = new int[grafo->getOrdem()];
    algoritmoGuloso();

}

Guloso::~Guloso()
{

}


void Guloso::algoritmoGuloso()
{
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
    quickSort(listaGraus,i,grafo->getOrdem()-1,listaIds,coloracao); //Ordenando do maior para o menor grau

    No* no;
    bool w = 1;
    int p,cont;
    int z=0;
    while(w)
    {
        z++;
        no = grafo->getNo(listaIds[i]);
        coloracao[i] = 2; //Pinta o Grafo de preto

        int q =0;


        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            for(p = 0; p < grafo->getOrdem(); p++)
            {
                if(listaIds[p] == aresta->getId_Alvo())
                    break;
            }

            if(coloracao[p] == 0) //Se for branco ok!
            {
                coloracao[p] = 1; //Os Adjacentes a ele se tornam cinzas
            }

            if(listaGraus[p] > -1)
                listaGraus[p] = listaGraus[p] - 1; //Diminui o Grau dos já conectados à ele
        }

        if(coloracao[i] ==2)
        {
            solucao[i] = no->getId();
            i++;
        }

        while(coloracao[q]!= -1 && q<grafo->getOrdem() )
        {
            cout<<"ID: "<<listaIds[q]<<" Colorido: "<<coloracao[q]<< " Com grau: "<<listaGraus[q]<<" Na inteiração:"<<z<< endl;
            q++;
        }
        quickSort(listaGraus,i,grafo->getOrdem()-1, listaIds,coloracao);

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
        cout << "Solucao " << solucao[t] << " ";
        t++;
    }
    cout << "Tamanho da solucao " << t << endl;
}

void Guloso::quickSort(int* vetor,int esquerda,int direita, int* indices, int* coloracao)
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
            swap(coloracao[i],coloracao[j]);
            i++;
            j--;
        }
    }

    if(j > esquerda)
        quickSort(vetor,esquerda,j,indices,coloracao);
    if(i < direita)
        quickSort(vetor,i,direita,indices,coloracao);
}


int Guloso::gerarSemente()
{
    int semente;
    semente = time(nullptr);

    return semente;
}

void Guloso::algoritmoGulosoRandomizado()
{
    int* listaGraus = new int[grafo->getOrdem()]; //Lista de Graus do Grafo, inicialmente não ordenada
    int* listaIds = new int[grafo->getOrdem()]; //Lista com os ids do Grafo
}

