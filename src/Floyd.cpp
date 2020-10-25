#include "Floyd.h"
#define INT_MAX 9999

Floyd::Floyd(Grafo* g,int** matrizPesos)
{
    this->n = g->getOrdem();
    A = new int*[n+1];
    B = new int*[n+1];

    for(int i = 0; i < n; i++)
    {
        A[i] = new int[n+1];
        B[i] = new int[n+1];
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(matrizPesos[i][j] == -1)
                A[i][j] = INT_MAX;
            else
                A[i][j] = matrizPesos[i][j];
        }


    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                if(A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
            }

    this->printSolucao(A);
}

Floyd::~Floyd()
{
    for(int i = 0; i < this->n; i++)
    {
        for(int j = 0; j < this->n; i++)
        {
            delete [] A[i];
            delete [] B[i];
        }
    }

    delete [] A;
    delete [] B;
}


void Floyd::printSolucao(int** dist)
{
    cout << endl << "ALGORITMO DE FLOYDMARSHELL" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << endl;
        for(int j = 0; j < n; j++)
        {
            if(dist[i][j] == INT_MAX)

                cout << "INFINITO";

            else
                cout << dist[i][j] << " ";
        }
    }
}

void Floyd::printSolucaoFile(fstream &outputFile)
{
    outputFile << endl << "ALGORITMO DE FLOYDMARSHELL" << endl;
    int** dist = this->A;
    for(int i = 0; i < n; i++)
    {
        outputFile << endl;
        for(int j = 0; j < n; j++)
        {
            if(dist[i][j] == INT_MAX)

                outputFile << " INFINITO ";

            else
                outputFile << dist[i][j] << " ";
        }
    }
}
