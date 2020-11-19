#include "Guloso.h"
#define MAX_INTERACOES 50 // Numero maximo de interações por chamada do guloso (varia entre os sistemas operacionais na ordem MAC > Linux>Windoes)


/**
* IMPORTANTE:
* As cores para coloração são:
* branco = 0
* cinza = 1
* preto = 2
*/

/*
* Construtor do guloso padrão, Armazena as informações do grafo e automaticamente chama o algoritmo guloso para iniciar
* @param:Grafo * grafo //Ponteiro do grafo onde procuuramos a solução do guloso.
*/
Guloso::Guloso(Grafo* grafo)
{
    this->alfa = 1;
    this->tamSolucao = 999999999;
    this->grafo=grafo;
    solucao = new int[grafo->getOrdem()];
    verifica = false;
    algoritmoGuloso();
}

/*
* Construtor do guloso Randomizado, Armazena as informações do grafo e do alfa
 e automaticamente chama o algoritmo guloso randomizado para iniciar
* @param:Grafo * grafo //Ponteiro do grafo onde procuuramos a solução do guloso.
* @param: double alfa // alfa passado para o usuario para influenciar a randomização do guloso.
*/
Guloso::Guloso(Grafo* grafo, double alfa)
{
    this->alfa = alfa;
    this->tamSolucao = 999999999;
    this->grafo=grafo;
    solucao = new int[grafo->getOrdem()];
    verifica = false;
    algoritmoGulosoRandomizado();
}
/*
* Destrutor
*/
Guloso::~Guloso()
{

}

/*
*  Função que usando as informações armazenadas no construtor executa todo o guloso e imprime a informação na tela e guarda ela na estrutura
*/
void Guloso::algoritmoGuloso()
{
    start = std::chrono::system_clock::now(); // Variavel para contar o tempo de execução

    /*Variaveis para coloração e para lista de candidatos*/
    int* listaGraus = new int[grafo->getOrdem()];
    int* listaIds = new int[grafo->getOrdem()];
    int* coloracao = new int[grafo->getOrdem()];
    bool primeiraInteracao = true;

    /*Inicializa toda a solucação com -1*/
    for(int k = 0; k < grafo->getOrdem(); k++)
        solucao[k] = -1;

    int i = 0;

    /*  Inicializa todas as listas */
    for(No* no = grafo->getPrimeiroNo(); no != nullptr; no = no->getProx())
    {
        listaGraus[i] = no->getGrauEntrada();
        listaIds[i] = no->getId();
        coloracao[no->getId()] = 0;
        i++;
    }

    i = 0;
    /*Ordenando os vetores usando o quicksort usando os graus como comparação */
    quickSort(listaGraus,i,grafo->getOrdem()-1,listaIds,coloracao);

    /* Variaveis de controle*/
    No* no;
    bool w = 1;
    int p,cont;
    int z=0;

    /*Estrtura que ira se repetir até o guloso ser resolvido */
    while(w)
    {
        z++;

        if(primeiraInteracao)
        {
            /*Se for a primeira interação pegamos o no com maior grau da lista e o pintamos de preto*/
            no = grafo->getNo(listaIds[i]);
            coloracao[i] = 2; //Pinta o Grafo de preto
            primeiraInteracao = false;
        }
        else
        {
            /*Apartir da segunda interação pegamos o no cinza com maior grau e o pintamos de preto*/
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

        /*Pintamos todos os Nós adjacentes ao novo nó preto de cinza e diminuimos seu grau em um*/
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

        /*Atualiza variavel de controle*/
        if(coloracao[i] == 2)
        {
            i++;
        }


        /*Ordena com novos graus*/
        quickSort(listaGraus,i,grafo->getOrdem()-1, listaIds,coloracao);

        cont = 0;

        /*Verifica se ainda existem nós brancos no grafo e se não existem finaliza a execução*/
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
    /* Preenche a lista de solução*/
    for(int n = 0; n < grafo->getOrdem(); n++)
    {
        if(coloracao[n] == 2)
        {
            solucao[t] = listaIds[n];
            t++;
        }

    }


    cout << endl;
    /* Estrutura que imprime quais foram os Nós escolhidos, comentada para fins de diminuir consumo de tempo*/
    /*cout<< "[";
    for(int r = 0; r < t; r++)
    {
        if(solucao[r] != -1)
            cout << solucao[r] << " ";
    }
    cout<<"]"<<endl;*/
    /* Atualiza o tamanho da informação*/
    this->tamSolucao = t;

    /*Calcula o tempo total da execução e imprime na tela o tempo e o tamanho da solução*/
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    duracao = elapsed_seconds.count();
    cout << "Tempo: " << duracao  << " resultado: " << t << endl;


    /*Apagando as listas*/
    delete [] listaIds;
    delete [] listaGraus;
    delete [] coloracao;

}

/*
* Função que executa o Guloso randomizado, usa informações do construtor. Imprime na tela e armazena as infomações
*/
void Guloso::algoritmoGulosoRandomizado()
{

    /*Inicio da Contagem de Tempo*/
    start = std::chrono::system_clock::now();

    /*Variaveis para coloração e para lista de candidatos*/
    int n = grafo->getOrdem();
    int* listaGraus = new int[n];
    int* listaIds = new int[n];
    int* coloracao = new int[n];
    int i,indiceSelecionado,candidatos;
    bool primeiraInteracao = true;

    /*Variavel para randomizar o vertice inicial*/
    candidatos = n;

    /*For que controla quantas interações o guloso passará antes de retornar a melhor resposta dessas interações*/
    for(int j = 0; j < MAX_INTERACOES; j++)
    {
        /*Inicializa toda a solucação com -1*/
        for(int k = 0; k < n; k++)
        {
            solucao[k] = -1;
        }

        i = 0;
        /*  Inicializa todas as listas */
        for(No* no = grafo->getPrimeiroNo(); no != nullptr; no = no->getProx())
        {
            listaGraus[i] = no->getGrauEntrada();
            listaIds[i] = no->getId();
            coloracao[no->getId()] = 0;
            i++;
        }

        i = 0;
        /*Ordenando os vetores usando o quicksort usando os graus como comparação */
        quickSort(listaGraus,i,n-1, listaIds,coloracao);

        /*Randomiza o primeiro indice da lista, não mais começando com o com maior grau*/
        if(candidatos == 0)
        {
            /*Devido a peculiaridades da função rand não se pode fazer um rand de 0 a 0, logo esse if*/
            indiceSelecionado = 0;
        }
        else
        {
            indiceSelecionado = rand()%(int)ceil((candidatos)*alfa);
        }

        /*Variaveis de controle*/
        candidatos--;
        No* no;
        bool w = 1;
        int p,cont;
        int z=0;

        /*Roda o guloso e acha a melhor resposta para o guloso que começa com o indice selecionado*/
        while(w)
        {
            z++;

            if(primeiraInteracao)
            {
                /*Se for a primeira interação, pintamos o No que o alfa randomizou de preto*/
                no = grafo->getNo(listaIds[indiceSelecionado]);
                coloracao[indiceSelecionado] = 2; //Pinta o Grafo de preto
            }
            else
            {
                /*Apartir da segunda pintamos o grau cinza de maior ordem*/
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
            /*Pintamos todos os Nós adjacentes ao novo nó preto de cinza e diminuimos seu grau em um*/
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
            /*Atualiza variavel de controle*/
            if(coloracao[i] == 2)
            {
                i++;
            }

            /*Ordena com novos graus*/
            quickSort(listaGraus,i,grafo->getOrdem()-1, listaIds,coloracao);

            /*Verifica se ainda existem nós brancos no grafo e se não existem finaliza essa interação do guloso e armazena a solução*/
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
        /*preenche a solução dessa interação do guloso*/
        for(int m = 0; m < grafo->getOrdem(); m++)
        {
            if(coloracao[m] == 2)
            {
                solucao[t] = listaIds[m];
                t++;
            }

        }
        /*Compara a solução dessa interação do guloso com a antiga melhor e guarda a melhor solução*/
        if(tamSolucao > t)
        {
            tamSolucao = t;
        }

    }


    /*Conclui a contagem de tempo e imprime na tela e guarda o tempo decorrido e a melhor solução entre todas as interações do guloso*/
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    duracao = elapsed_seconds.count();
    cout << "Tempo: " << duracao << " tamanho: " << tamSolucao << endl;

    /*Apagando as listas*/
    delete [] listaIds;
    delete [] listaGraus;
    delete [] coloracao;
}

/*
* Função responsavel pela impressão da solução do algoritmo guloso e guloso randomizado no arquivo de saida, escolhe qual baseado na existencia do alfa
* @param: fstream &outputFile // Arquivo onde será feita a impressão.
*/
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


/*
*Estrtura de ordenação usada na lista de graus, além disso ela arruma a posição nas duas outras listas quando mexe na de gaus
* @param:int* vetor // Vetor de graus que será ordenado
* @param:int esquerda // inicio da ordenaçãp
* @param:int direita // fim de ordenação
* @param:int* indices //  Vetor de indices que tera suas posições alteradas conforme a lista de graus é ordenada
* @param:int* coloracao //  Vetor de coloração que tera suas posições alteradas conforme a lista de graus é ordenada
*/
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


/*
*  Função usada para verificar se a resposta do guloso encontrada, padrão ou randomizado, é valida. Usa uma variavel para armazenar a informação
*/
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



