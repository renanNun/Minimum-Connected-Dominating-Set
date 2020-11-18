#include "Guloso.h"
#define MAX_INTERACOES 28

/*
* Cores para coloração
* branco = 0
* cinza = 1
* preto = 2
*/

Guloso::Guloso(Grafo* grafo)
{
    this->alfa = 1;
    this->tamSolucao = 999999999;
    this->grafo=grafo;
    algoritmoGuloso();
    verifica = false;

}

Guloso::Guloso(Grafo* grafo, double alfa)
{
    this->alfa = alfa;
    this->tamSolucao = 999999999;
    this->grafo=grafo;
    algoritmoGulosoRandomizado();
    verifica = false;
}

Guloso::~Guloso()
{
    delete [] solucao;
    delete [] listaGraus;
    delete [] listaIds;
    delete [] coloracao;
}


void Guloso::algoritmoGuloso()
{
    start(); //Começo o algoritmo
    iniciaVetores(); //Inicia os vetores
    bool primeiraInteracao = true;

    resetaSolucaoTemporaria();

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
    while(w)
    {

        if(primeiraInteracao) //Caso seja a primeira interação
        {
            no = grafo->getNo(listaIds[i]);
            coloracao[i] = 2; //Pinta o Grafo de preto
            primeiraInteracao = false;
        }
        else
        {
            for(int l = 0; l < grafo->getOrdem(); l++)
            {
                if(coloracao[l] == 1)
                {
                    no = grafo->getNo(listaIds[l]);
                    coloracao[l] = 2;
                    break;
                }
            }
        }

        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            for(p = 0; p < grafo->getOrdem(); p++)
            {
                if(listaIds[p] == aresta->getId_Alvo())
                {
                    break;
                }

            }

            if(coloracao[p] == 0) //Se for branco ok!
            {
                coloracao[p] = 1; //Os Adjacentes a ele se tornam cinzas
            }

            if(listaGraus[p] > -1)
                listaGraus[p] = listaGraus[p] - 1; //Diminui o Grau dos já conectados à ele
        }

        if(coloracao[i] == 2)
        {
            i++;
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
    for(int n = 0; n < grafo->getOrdem(); n++)
    {
        if(coloracao[n] == 2)
        {
            solucao[t] = listaIds[n];
            t++;
        }

    }

    this->tamSolucao = t;
    verificaResposta();

    finish();
    cout << "Tempo: " << duracao  << " resultado: " << t << endl;

}

void Guloso::verificaResposta()
{
    Grafo verifica;
    int cont = 0;
    for(int i = 0; i < this->grafo->getOrdem(); i++)
    {
        if(solucao[i] != -1)
        {
            verifica.inserirNo(this->solucao[i]);
            cont++;
        }

    }
    verifica.setOrdem(cont); //Colocamos aqui a ordem do subgrafo induzido

    for(int i = 0; i < this->grafo->getOrdem(); i++)
    {
        No* no = this->grafo->getPrimeiroNo();
        while(no != nullptr)
        {
            if(solucao[i] != -1)
            {
                if(solucao[i] == no->getId())
                {
                    for(Aresta* a = no->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
                    {
                        for(int j = 0; j < this->grafo->getOrdem(); j++)
                        {
                            if(solucao[j] == -1)
                            {
                                break;
                            }

                            if(solucao[j] == a->getId_Alvo())
                            {
                                verifica.inserirAresta(solucao[i],solucao[j],0);
                            }
                        }
                    }
                }
            }
            no = no->getProx();
        }
    }

    verifica = verifica.ehConexo();

}

void Guloso::algoritmoGulosoRandomizado()
{
    start();
    /*Inicio da Contagem de Tempo*/

    iniciaVetores();

    int n = grafo->getOrdem();
    int i,indiceSelecionado,candidatos;
    bool primeiraInteracao = true;
    candidatos = n;

    //Possui máximo de interações

    for(int j = 0; j < MAX_INTERACOES; j++)
    {
        resetaSolucaoTemporaria();


        i = 0;
        for(No* no = grafo->getPrimeiroNo(); no != nullptr; no = no->getProx()) //Iniciando graus e ids
        {
            listaGraus[i] = no->getGrauEntrada();
            listaIds[i] = no->getId();
            coloracao[no->getId()] = 0;
            i++;
        }

        i = 0;
        quickSort(listaGraus,i,n-1, listaIds,coloracao);
        if(candidatos == 0)
        {
            indiceSelecionado = 0;
        }
        else
        {
            indiceSelecionado = rand()%(int)ceil((candidatos)*alfa);
        }

        No* no;
        bool w = 1;
        int p,cont;
        while(w)
        {

            if(primeiraInteracao)
            {
                no = grafo->getNo(listaIds[indiceSelecionado]);
                coloracao[indiceSelecionado] = 2; //Pinta o Grafo de preto
            }
            else
            {
                for(int l = 0; l < grafo->getOrdem(); l++)
                {
                    if(coloracao[l] == 1)
                    {
                        no = grafo->getNo(listaIds[l]);
                        coloracao[l] = 2;
                        break;
                    }
                }
            }

            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
            {
                for(p = 0; p < grafo->getOrdem(); p++)
                {
                    if(listaIds[p] == aresta->getId_Alvo())
                    {
                        break;
                    }

                }

                if(coloracao[p] == 0) //Se for branco ok!
                {
                    coloracao[p] = 1; //Os Adjacentes a ele se tornam cinzas
                }

                if(listaGraus[p] > -1)
                    listaGraus[p] = listaGraus[p] - 1; //Diminui o Grau dos já conectados à ele
            }

            /*Forçando ele a ficar no inicio da lista*/
            if(primeiraInteracao)
            {
                forcaInicio(i,indiceSelecionado);
                primeiraInteracao = false;
            }

            if(coloracao[i] == 2)
            {
                candidatos--;
                i++;
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
        primeiraInteracao = true;
        int t = 0;
        for(int m = 0; m < grafo->getOrdem(); m++)
        {
            if(coloracao[m] == 2)
            {
                solucao[t] = listaIds[m];
                t++;
            }

        }
        if(tamSolucao > t)
        {
            tamSolucao = t;
        }
    }

    finish();
    cout << "Tempo: " << duracao << " tamanho: " << tamSolucao << endl;
}

void Guloso::imprime(fstream &outputFile)
{
    if(alfa == 1)
    {
        outputFile << this->tamSolucao << ";" << duracao << endl;
    }
    else
    {
        outputFile << this->tamSolucao << ";" << duracao << ";" << alfa << endl;
    }
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

/**
  Começa a contagem de tempo
*/
void Guloso::start()
{
    init = std::chrono::system_clock::now();
}

/**
    Termina Contagem de Tempo e realiza a contagem
*/
void Guloso::finish()
{
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - init;
    duracao = elapsed_seconds.count();
}

/**
    Inicia todos os vetores com tamanho n, onde n é a ordem do grafo
*/
void Guloso::iniciaVetores()
{
    int n = this->grafo->getOrdem();

    solucao = new int [n];
    listaGraus = new int[n];
    listaIds = new int[n];
    coloracao = new int[n];
}

void Guloso::resetaSolucaoTemporaria()
{
    //Inicializa toda a solucação com -1
    for(int k = 0; k < grafo->getOrdem(); k++)
        solucao[k] = -1;
}

void Guloso::forcaInicio(int i,int j)
{
    swap(listaGraus[i],listaGraus[j]);
    swap(listaIds[i],listaIds[j]);
    swap(coloracao[i],coloracao[j]);
}
