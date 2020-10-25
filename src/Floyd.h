#ifndef FLOYD_H
#define FLOYD_H

#include "Grafo.h"
#include <fstream>

using namespace std;

class Floyd
{
public:
    Floyd(Grafo* g, int** matrizPesos);
    ~Floyd();

    void algoritmo();
    void printSolucao(int** dist);
    void printSolucaoFile(fstream &outputFile);

private:
    int n;
    int** A;
    int** B;
};

#endif // FLOYD_H
