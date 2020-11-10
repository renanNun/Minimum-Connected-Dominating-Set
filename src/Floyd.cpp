#include "Floyd.h"
#define INT_MAX 999999

Floyd::Floyd(Grafo* grafo)
{
    this->n = grafo->getOrdem();

    this->pesoArestas = new int*[n];
    this->distanciaArestas = new int*[n];

    for(int i = 0; i < n; i++)
    {
        this->pesoArestas[i] = new int[n];
        this->distanciaArestas[i] = new int[n];
    }

    iniciaMatrizes(grafo);
    floydWarshall();
    imprimeSolucao();
}

Floyd::~Floyd()
{
    for(int i = 0; i < this->n; i++)
    {
        delete [] this->pesoArestas[i];
        delete [] this->distanciaArestas[i];
    }

    delete [] this->pesoArestas;
    delete [] this->distanciaArestas;
}

void Floyd::iniciaMatrizes(Grafo* grafo)
{
    No* no = grafo->getPrimeiroNo();
    for(int i = 0; i < n && no != nullptr; i++)
    {
        no->setI(i);
        no = no->getProx();
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                this->pesoArestas[i][j] = 0;
            else
                this->pesoArestas[i][j] = INT_MAX;
        }


    for(No* no = grafo->getPrimeiroNo(); no != nullptr; no = no->getProx())
    {
        for(Aresta* a = no->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
        {
            No* aux = grafo->getNo(a->getId_Alvo());
            this->pesoArestas[no->getI()][aux->getI()] = a->getPeso();
        }
    }
}

void Floyd::floydWarshall()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            this->distanciaArestas[i][j] = this->pesoArestas[i][j];

    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                if(this->distanciaArestas[i][k] + this->distanciaArestas[k][j] < this->distanciaArestas[i][j])
                    this-> distanciaArestas[i][j] = this->distanciaArestas[i][k] + this->distanciaArestas[k][j];
            }
}

void Floyd::imprimeSolucao()
{
    cout << endl << "Matriz de Floyd Warshall" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << endl;
        for(int j = 0; j < n; j++)
        {
            if(this->distanciaArestas[i][j] == INT_MAX)
                cout << " INFINITO ";
            else
                cout << this->distanciaArestas[i][j] << " ";
        }
    }
}

void Floyd::imprimeSolucaoFile(fstream &outputFile)
{
    outputFile << endl << "Matriz de Floyd Warshall" << endl;
    for(int i = 0; i < n; i++)
    {
       outputFile << endl;
        for(int j = 0; j < n; j++)
        {
            if(this->distanciaArestas[i][j] == INT_MAX)
                outputFile << " INFINITO ";
            else
                outputFile << this->distanciaArestas[i][j] << " ";
        }
    }
}

