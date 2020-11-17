#include "Guloso.h"
#define MAX_INTERACOES 10

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
    solucao = new int[grafo->getOrdem()];
    algoritmoGuloso();

}

Guloso::Guloso(Grafo* grafo, double alfa)
{
    this->alfa = alfa;
    this->tamSolucao = 999999999;
    this->grafo=grafo;
    solucao = new int[grafo->getOrdem()];
    algoritmoGulosoRandomizado();
}

Guloso::~Guloso()
{

}


void Guloso::algoritmoGuloso()
{
    start = std::chrono::system_clock::now();

    int* listaGraus = new int[grafo->getOrdem()];
    int* listaIds = new int[grafo->getOrdem()];
    int* coloracao = new int[grafo->getOrdem()];
    bool primeiraInteracao = true;
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

        if(primeiraInteracao)
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

        int q =0;

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
            //solucao[i] = no->getId();
            i++;
        }

        /*for(int m = 0; m < grafo->getOrdem(); m++)
        {
            cout << "ID: " << listaIds[m] << " colorido: " << coloracao[m] << " com grau: " << listaGraus[m] << " na interacao: " << z << endl;
        }*/

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
            //cout << " lista " << listaIds[n];
            solucao[t] = listaIds[n];
            //cout << " SolucaoN: " << solucao[n];
            t++;
        }

    }


    cout << endl;
    cout<< "[";
    for(int r = 0; r < t; r++)
    {
        if(solucao[r] != -1)
            cout << solucao[r] << " ";
    }
    cout<<"]"<<endl;
    this->tamSolucao = t;
    cout << verificaResposta();
    cout << "Terminou" << endl;
    /*if()
    {
        cout<< "Deu certo"<<endl;

    }
    else
    {
        cout<< "Deu errado<<"<<endl;
    }*/
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    duracao = elapsed_seconds.count();
    cout << "Tempo: " << duracao  << " resultado: " << t << endl;
}

bool Guloso::verificaResposta()
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

    bool x = verifica.ehConexo();
    //cout << "verificou " << x << endl;
    return x;
}

void Guloso::algoritmoGulosoRandomizado()
{
    start = std::chrono::system_clock::now();

    int tam = grafo->getOrdem();
    int* solucaoFinal = new int[tam];
    int* listaGraus = new int[tam];
    int* listaIds = new int[tam];
    int* coloracao = new int[tam];
    bool w = true;
    bool primeiraInteracao = true;

    for(int h = 0; h < MAX_INTERACOES; h++)
    {
        //Inicializa toda a solucação com -1
        for(int k = 0; k < tam; k++)
        {
            solucao[k] = -1;
            solucaoFinal[k] = -1;
        }
        int i = 0;
        for(No* no = grafo->getPrimeiroNo(); no != nullptr; no = no->getProx()) //Iniciando graus e ids
        {
            listaGraus[i] = no->getGrauEntrada();
            listaIds[i] = no->getId();
            coloracao[no->getId()] = 0;
            i++;
        }

        //int x = rand() % (int)((tam) * alfa);
        i = 0;
        tamSolucao = tam * alfa;
        quickSort(listaGraus,i,tamSolucao,listaIds,coloracao); //Ordenando do maior para o menor grau
        //cout << "PRIMEIRO QUICK SORT" << endl;
        No* no;
        w = true;
        int p,cont;
        int z=0;
        while(w)
        {
            //cout << "DENTRO DO WHILE " << z << endl;
            z++;

            if(primeiraInteracao)
            {
                //cout << "Entra aqui " << endl;
                no = grafo->getNo(listaIds[i]);
                coloracao[i] = 2; //Pinta o Grafo de preto
                primeiraInteracao = false;
            }
            else
            {
                //cout << "ENTRA AQUi" << endl;
                for(int l = 0; l < tam; l++)
                {
                    if(coloracao[l] == 1)
                    {
                        no = grafo->getNo(listaIds[l]);
                        //cout << " " << no->getId();
                        coloracao[l] = 2;
                        break;
                    }
                }
            }


            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
            {
                //cout << "ARESTAS" << endl;
                for(p = 0; p < tam; p++)
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

            for(int m = 0; m < grafo->getOrdem(); m++)
            {
                cout << "ID: " << listaIds[m] << " colorido: " << coloracao[m] << " com grau: " << listaGraus[m] << " na interacao: " << z << " do max int: " << h<< endl;
            }

            quickSort(listaGraus,i,tam, listaIds,coloracao);

            cont = 0;
            for(int k = 0; k < grafo->getOrdem(); k ++)
            {
                cont++;

                if(coloracao[k] == 0)
                {
                    break;
                }
            }

            if(cont == tam)
            {
                w = false;
                //cout << "FALSE" << endl;
            }

        }

        primeiraInteracao = true;

        int t = 0;
        for(int n = 0; n < tam; n++)
        {
            if(coloracao[n] == 2)
            {
                //cout << " lista " << listaIds[n];
                solucao[t] = listaIds[n];
                //cout << " SolucaoN: " << solucao[n];
                t++;
            }

        }
        //cout << " " << t;
        if(tamSolucao > t)
        {
            tamSolucao = t;
        }
    }

    cout << endl;
    /*for(int r = 0; r < tamSolucao; r++)
    {
        if(solucaoFinal[r] != -1)
            cout << "Solucao " << solucao[r] << " ";
    }*/

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    duracao = elapsed_seconds.count();
    cout << "Tempo: " << duracao  << " resultado: " << tamSolucao << endl;
}

int Guloso::gerarSemente()
{
    int semente;
    semente = time(nullptr);

    return semente;
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

