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
    verifica = false;

}

Guloso::Guloso(Grafo* grafo, double alfa)
{
    this->alfa = alfa;
    this->tamSolucao = 999999999;
    this->grafo=grafo;
    solucao = new int[grafo->getOrdem()];
    algoritmoGulosoRandomizado();
    verifica = false;
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
    verificaResposta();

    if(verifica)
    {

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        duracao = elapsed_seconds.count();
        cout << "Tempo: " << duracao  << " resultado: " << t << endl;
    }
    else
    {
        cout <<" resultado insatisfatorio"<<endl;
    }


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
    start = std::chrono::system_clock::now();
    /*Inicio da Contagem de Tempo*/

    int n = grafo->getOrdem();
    int* listaGraus = new int[n];
    int* listaIds = new int[n];
    int* coloracao = new int[n];
    int i,indiceSelecionado,candidatos;
    bool primeiraInteracao = true;
    candidatos = n;
    //Possui máximo de interações
    cout << "Antes de entrar no randomizado " << endl;
    for(int j = 0; j < MAX_INTERACOES; j++)
    {
        for(int k = 0; k < n; k++)
        {
            solucao[k] = -1;
        }


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
        } else {
            indiceSelecionado = rand()%(int)ceil((candidatos)*alfa);
        }

        cout << "indice selecionado: " << listaIds[indiceSelecionado] << endl;
        candidatos--;
        No* no;
        bool w = 1;
        int p,cont;
        int z=0;
        while(w)
        {
            z++;

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
                swap(listaGraus[i],listaGraus[indiceSelecionado]);
                swap(listaIds[i],listaIds[indiceSelecionado]);
                swap(coloracao[i],coloracao[indiceSelecionado]);
                primeiraInteracao = false;
            }

            if(coloracao[i] == 2)
            {
                i++;
            }

            /*for(int m = 0; m < grafo->getOrdem(); m++)
            {
                cout << "ID: " << listaIds[m] << " colorido: " << coloracao[m] << " com grau: " << listaGraus[m] << " na interacao: " << z << " no max_int: " << j << endl;
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

    /*Fim Contagem de Tempo*/
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    duracao = elapsed_seconds.count();
    cout << "Tempo: " << duracao << " tamanho: " << tamSolucao << endl;
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

