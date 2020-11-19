#include "Prim.h"
#define INFINITO 999999


/*
* Construtor  da classe Prim
* @param: Grafo* grafo // Ponteiro do grafo que se espera a solu��o de Prim
* @param: int no_escolhido // Id do No escolhido para come�ar a analise do algoritmo de Prim
*/

Prim::Prim(Grafo* grafo, int no_escolhido)
{
    this->grafo = grafo;
    noEscolhido = grafo->getNo(no_escolhido);
    algoritmoDePrim();
}

/*
* Destrutor da classe Prim
*
*/
Prim::~Prim()
{

}

/*
* Fun��o que resolve o algoritmo de Prim usando as informa��es previamente armazenadas no construtor.
*/
void Prim::algoritmoDePrim()
{

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
                        }
                        else
                        {
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
    imprime();
}

/*
* Fun��o responsavel pela impress�o da solu��o do algoritmo de Prim na tela
*/
void Prim::imprime()
{
    cout << "PRIM" << endl;
    int pesoFinal=0;
    for(Aresta* & arestaAux : arestasArvore)
    {
        cout << arestaAux->getId_Origem() << "-->" << arestaAux->getId_Alvo() << " " << arestaAux->getPeso() << endl;
        pesoFinal= pesoFinal + arestaAux->getPeso();

    }
    cout << endl;
    cout<<"O peso final da solu��o do algoritmo de Prim � : "<<pesoFinal<<endl;

}

/*
* Fun��o responsavel pela impress�o da solu��o do algoritmo de Prim no arquivo de saida
* @param: fstream &outputFile // Arquivo onde ser� feita a impress�o.
*/

void Prim::imprimeFile(fstream &outputFile)
{
    cout << "PRIM" << endl;
    int pesoFinal=0;
    for(Aresta* & arestaAux : arestasArvore)
    {
        outputFile << arestaAux->getId_Origem() << "-->" << arestaAux->getId_Alvo() << " Com peso:  " << arestaAux->getPeso() << endl;
        pesoFinal= pesoFinal + arestaAux->getPeso();

    }
    outputFile << endl;
    outputFile<<"O peso final da solucao do algoritmo de Prim � : "<<pesoFinal<<endl;
}
