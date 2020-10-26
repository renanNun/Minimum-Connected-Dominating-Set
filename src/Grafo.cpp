#include "Grafo.h"

/*
* Construtor vazio da classe Grafos, inicia todos os parametros como null ou 0;
*/
Grafo::Grafo()
{
    this->ordem = 0;
    this->numero_arestas = 0;
    this->direcionado = false;
    this->ponderado_aresta = false;
    this->ponderado_no = false;
    this->primeiro_no = this->ultimo_no = nullptr;

    this->matriz_adjacencia = nullptr;
    this->matriz_pesos = nullptr;
    this->inicializaMatrizes();
}

/*
* Construtor com apenas Um dos parametros da classe Grafos, inicia a ordem e deixa todos os outros parametros como null ou 0;
* @param: Int ordem // recebe a ordem dos grafos
*/
Grafo::Grafo(int ordem)
{
    this->ordem = ordem;
    this->numero_arestas = 0;
    this->direcionado = false;
    this->ponderado_aresta = false;
    this->ponderado_no = false;
    this->primeiro_no = this->ultimo_no = nullptr;

    this->matriz_adjacencia = nullptr;
    this->matriz_pesos = nullptr;
    this->inicializaMatrizes();
}

/*
* Construtor completo da classe Grafos,
* inicia todos os parametros recebidos e deixa os outros nulos para serem preenchidos pelo "incializaMatrizes();
* @param: Int ordem // recebe a ordem dos grafos
* @param:  bool direcionado // booleano que indica se o grafo é direcionado
* @param: bool ponderado_aresta // booleano que indica se as arestas são ponderadas
* @param: bool ponderado_no// booleano que indica se os Nos são ponderados
*/
Grafo::Grafo(int ordem, bool direcionado,bool ponderado_aresta,bool ponderado_no)
{
    this->ordem = ordem;
    this->numero_arestas = 0;
    this->direcionado = direcionado;
    this->ponderado_aresta = ponderado_aresta;
    this->ponderado_no = ponderado_no;
    this->primeiro_no = this->ultimo_no = nullptr;

    this->matriz_adjacencia = nullptr;
    this->matriz_pesos = nullptr;
    this->inicializaMatrizes();
}

/*
* Destrutor
*/
Grafo::~Grafo()
{
    this->deleteMatrizes();

    No* proximo_no = this->primeiro_no;
    while(proximo_no != nullptr)
    {
        proximo_no->removerTodasArestas();
        No* aux = proximo_no->getProx();
        delete proximo_no;
        proximo_no = aux;
    }
}

/*Getters e Setters*/
int Grafo::getOrdem()
{
    return this->ordem;
}

int Grafo::getNumeroArestas()
{
    return this->numero_arestas;
}

bool Grafo::getDirecionado()
{
    return this->direcionado;
}

bool Grafo::getPonderadoAresta()
{
    return this->ponderado_aresta;
}

bool Grafo::getPonderadoNo()
{
    return this->ponderado_no;
}

No* Grafo::getPrimeiroNo()
{
    return this->primeiro_no;
}

No* Grafo::getUltimoNo()
{
    return this->ultimo_no;
}

void Grafo::setOrdem(int ordem)
{
    this->ordem = ordem;
}

void Grafo::setNumeroArestas(int numeroArestas)
{
    this->numero_arestas = numeroArestas;
}

/*Funções do Grafo*/

/*
* Função que aumenta em um o numero de arestas registradas
*/

void Grafo::aumentaNumArestas()
{
    this->numero_arestas++;
}

/*
* Função que diminui em um o numero de arestas registradas se o numero for maior que 0
*/
void Grafo::diminuiNumArestas()
{
    if(this->numero_arestas > 0)
        this->numero_arestas--;
    else
        cout<< "É impossivel deixar o numero de arestas negativo"<<endl;
}

/*
* Função que retorna o ponteiro para o Nó com Id indicado
* @param: int Id// Id do nó desejado
* @return: Ponteiro para o Nó com id recebido
*/
No* Grafo::getNo(int id)
{
    if(this->primeiro_no != nullptr)
    {
        for(No* aux = this->primeiro_no; aux != nullptr; aux = aux->getProx())
            if(aux->getId() == id)
                return aux;
    }
    else
    {
        cout << "O Nó indicado não existe, retornando Null"<< endl;
    }

    return nullptr;
}

/*
* Função que verifica a existencia ddo Nó com id passado.
* @param: int Id// Id do nó desejado
* @return: booleano que representa a existencia do Nó
*/
bool Grafo::existeNo(int id)
{
    if(this->primeiro_no != nullptr)
    {
        for(No* aux = this->primeiro_no; aux != nullptr; aux = aux->getProx())
            if(aux->getId() == id)
                return true;
    }

    return false;
}

/*
* Função que insere um Nó no grafo com o Id que foi passado.
* @param: int Id// Id do nó a ser incluido
*/
void Grafo::inserirNo(int id)
{
    if(!existeNo(id))
    {
        if(this->primeiro_no != nullptr)
        {
            No* no = new No(id);
            this->ultimo_no->setProxNo(no);
            this->ultimo_no = no;
        }
        else
        {
            this->primeiro_no = new No(id);
            this->ultimo_no = this->primeiro_no;
        }
    }
    else
        cout << "O Nó com esse Id Já existe"<<endl;
}
/*
* Função que remove um Nó no grafo com o Id que foi passado.
* @param: int Id// Id do nó a ser removido
*/
void Grafo::removerNo(int id)
{
    if(existeNo(id))
    {
        if(this->primeiro_no->getId() == id)
        {
            No* aux = this->primeiro_no;
            this->primeiro_no = this->primeiro_no->getProx();
            delete aux;
        }
        else
        {

            No* anterior;
            No* aux = this->primeiro_no;

            while(aux != nullptr)
            {
                if(aux->getId() == id)
                {
                    break;
                }

                anterior = aux;
                aux = aux->getProx();
            }

            if(this->ultimo_no == aux)
            {
                this->ultimo_no = anterior;
            }

            anterior->setProxNo(aux->getProx());

            No* p = this->primeiro_no;
            while(p != nullptr)
            {
                p->removerAresta(id,direcionado,p);
            }

            delete aux;
        }
    }
}

/*
* Função que insere umaa aresta que começa no id e vai até o id_alvo e tem peso representado pela variavel "peso".
* @param: int Id// Id do Nó de onde a aresta sai
* @param: int id_alvo// Id do Nó que receberá a aresta
* @param: int peso// peso da aresta a ser criada.
*/
void Grafo::inserirAresta(int id,int id_alvo,int peso)
{
    if(!existeNo(id))
        this->inserirNo(id);

    if(!existeNo(id_alvo))
        this->inserirNo(id);

    if(this->direcionado)
    {
        No* no = getNo(id);
        No* no_alvo = getNo(id_alvo);
        no->inserirAresta(id_alvo,peso);
        no->aumentaGrauSaida();
        no_alvo->aumentaGrauEntrada();
    }
    else
    {
        No* no = getNo(id);
        no->inserirAresta(id_alvo,peso);
        no->aumentaGrauEntrada();
    }
}

/*
* Função que calcula e retorna o Grau medio, usando o metodo de somatorio
* @return: inteiro que representa o grau medio do grafo usando somatorio
*/
int Grafo::grauMedioPorSomatorio()
{
    if(this->ordem != 0)
    {
        No* percorreGrafo = this->primeiro_no;
        int somatorioGraus = 0;

        if(!this->direcionado)
        {
            while(percorreGrafo->getProx() != nullptr)
            {
                somatorioGraus += percorreGrafo->getGrauEntrada();
                percorreGrafo = percorreGrafo->getProx();
            }
        }
        else
        {
            while(percorreGrafo->getProx() != nullptr)
            {
                somatorioGraus += percorreGrafo->getGrauSaida();
                percorreGrafo = percorreGrafo->getProx();
            }


        }


        int grauMedio = somatorioGraus/this->ordem;
        return grauMedio;
    }
    else
    {
        cout << "Nao e possível calcular o grau medio sem nos no grafo";
        return -1;
    }
}
/*
* Função que calcula e retorna o Grau medio, usando o metodo de adjacencia
* @return: inteiro que representa o grau medio do grafo usando adjacencia
*/
int Grafo::grauMedioPorAdjacencia()
{
    if(this->ordem != 0)
    {
        int grauMedio = (2) * (this->numero_arestas/this->ordem);
        return grauMedio;
    }
    else
    {
        cout << "Nao e possível calcular o grau medio sem nos no grafo";
        return -1;
    }
}
/*
* Função que calcula e retorna a frequencia relativa de grau d
* @param: int d// parametro de comparação
* @return: inteiro que representa a frequencia relativa do grafo
*/
int Grafo::frequenciaRelativa(int d)
{
    if(this->primeiro_no == nullptr)
        return 0;
    else
    {
        int cont = 0;

        for(No* no = this->primeiro_no; no != nullptr; no = no->getProx())
        {
            if(no->getGrauEntrada() == d)
                cont++;
        }

        return (cont/this->ordem);
    }
}
/*
* Função que retorna o numero de nos do Grafo
* @return: inteiro que representa o grau do Grafo
*/
int Grafo::grauDoGrafo()
{
    int grau = 0;

    for(No* no = this->primeiro_no; no != nullptr; no = no->getProx())
    {
        if(no->getGrauEntrada() > grau)
            grau = no->getGrauEntrada();
    }

    return grau;
}
/*
* Função que usa a matriz de adjacencia pra verificar se existe adjacencia entre dois Nos.
* @param: int i// parametro que representa a posição do No na matriz
* @param: int j// parametro que representa a posição do No na matriz
* @return: booleano que representa a existencia da adjacencia entre as duas posições
*/
bool Grafo::verificaAdjacencia(int i,int j)
{
    if(this->matriz_adjacencia[i][j])
        return true;
    return false;
}

/*
* Função que adiciona uma aresta na matriz de pesos, da posição i e j com peso "peso".
* @param: int i// parametro que representa a posição do No na matriz
* @param: int j// parametro que representa a posição do No na matriz
* @param: int peso// parametro que representa o peso da matriz a ser adicionada
*/
void Grafo::adicionaArestaMatriz(int i,int j, int peso)
{
    matriz_adjacencia[this->getPosicaoMatriz(i)][this->getPosicaoMatriz(j)] = true;
    matriz_pesos[this->getPosicaoMatriz(i)][this->getPosicaoMatriz(j)] = peso;
}

/*
* Função que pega a posição do No com o id passado nas matrizes
* @param: int id// parametro que representao Nó a ser buscado nas matrizes
* @return: inteiro que representa a posição do No com id recebido nas matrizes
*/
int Grafo::getPosicaoMatriz(int id)
{
    int c = 0;

    for(No* no = this->primeiro_no; no != nullptr; no = no->getProx())
    {
        if(no->getId() == id)
        {
            return c;
        }
        c++;
    }

    return -1;
}

/*
* Função usada no construtor para incializar ambas as matrizes
*/
void Grafo::inicializaMatrizes()
{
    this->matriz_adjacencia = new bool*[this->ordem];
    this->matriz_pesos = new int*[this->ordem];

    for(int i = 0; i < this->ordem; i++)
    {
        this->matriz_adjacencia[i] = new bool[this->ordem];
        this->matriz_pesos[i] = new int[this->ordem];
        for(int j = 0; j < this->ordem; j++)
        {
            this->matriz_adjacencia[i][j] = false;
            this->matriz_pesos[i][j] = -1;
        }
    }
}

/*
* Função que funciona como destrutor para ambas as matrizes
*/
void Grafo::deleteMatrizes()
{
    for(int i = 0; i < this->ordem; i++)
    {
        for(int j = 0; j < this->ordem; j++)
        {
            delete [] matriz_adjacencia[i];
            delete [] matriz_pesos[i];
        }
        delete [] matriz_adjacencia;
        delete [] matriz_pesos;
    }
}

/*Impressões*/
string Grafo::imprimir()
{
    stringstream stream;
    stream << endl << endl << "\t\t Impressao por Lista de Adjacencia " << endl << endl;

    for(No* no = this->primeiro_no; no != nullptr; no = no->getProx())
    {
        stream << no->getId();

        if(no->getPrimeiraAresta() != nullptr)
            stream << "--->";

        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
        {
            if(this->ponderado_aresta)
            {
                if(aresta->getProxAresta() != nullptr)
                    stream << aresta->getId_Alvo() << "(" << aresta->getPeso() << ")--->";
                else
                    stream << aresta->getId_Alvo() << "(" << aresta->getPeso() << ")";
            }
            else
            {
                if(aresta->getProxAresta() != nullptr)
                    stream << aresta->getId_Alvo() << "--->";
                else
                    stream << aresta->getId_Alvo();
            }
        }
        stream << endl;
    }

    return stream.str();
}

string Grafo::imprimirMatriz()
{
    stringstream stream;
    stream << endl << endl << "\t\tImpressao por Matriz de Adjacencia" << endl << endl;
    for(int i = 0; i < this->ordem; i++)
    {
        stream << endl;
        for(int j = 0; j < this->ordem; j++)
        {
            stream << matriz_adjacencia[i][j] << " | ";
        }
    }

    return stream.str();
}

/*Buscas*/

/*
* Função que faz busca em profundidade partindo do Nó com id passado.
* @param: int id_inicial// parametro que representa o id do Nó em que a busca será iniciado
*/
bool Grafo::depthFirstSearch(int id_inicial)
{
    bool* vetor_coloracao = new bool[this->ordem];
    No* no = this->primeiro_no;

    for(int i = 0; i < this->ordem; i++)
    {
        no->setI(i);
        vetor_coloracao[i] = 0;
        no = no->getProx();
    }

    int nivel;
    No* pai = nullptr;
    no = getNo(id_inicial);

    cout << "BUSCA EM PROFUNDIDADE A PARTIR DO NO " << id_inicial << endl << endl;


    if(no != nullptr)
    {
        depthFirstSearchF(no,vetor_coloracao,pai,0);
    }
    else
    {
        cout << "NO NAO ENCONTRADO" << endl;
        return false;
    }

    delete [] vetor_coloracao;
    return true;
}

/*
* Função auxiliar da busca em profundidade.
* @param: int id_inicial// parametro que representa o id do Nó em que a busca será iniciado
*/
void Grafo::depthFirstSearchF(No* no, bool* vetor_coloracao, No* pai, int nivel)
{
    if(no == nullptr)
        return;

    if(nivel == 0)
    {
        cout << "NO: " <<  no->getId() << " PAI: NULL NIVEL: " << nivel << endl;
    }
    else
    {
        cout << "NO: " <<  no->getId() << " PAI: " << pai->getId() << " NIVEL: " << nivel << endl;
    }

    vetor_coloracao[no->getI()] = 1;
    Aresta* aresta = no->getPrimeiraAresta();

    while(aresta != nullptr)
    {
        No* aux = getNo(aresta->getId_Alvo());
        if(vetor_coloracao[aux->getI()] == 0)
            depthFirstSearchF(aux,vetor_coloracao,no,nivel+1);
        aresta = aresta->getProxAresta();
    }
}

/*
* Função que imprime o resultado da busca no arquivo.
* @param: int id_inicial// parametro que representa o id do Nó em que a busca será iniciado
* @param: fstream &outputFile// caminho do arquivo que salva a impressão
*/
bool Grafo::depthFirstSearchFile(int id_inicial,fstream &outputFile)
{
    bool* vetor_coloracao = new bool[this->ordem];
    No* no = this->primeiro_no;

    for(int i = 0; i < this->ordem; i++)
    {
        no->setI(i);
        vetor_coloracao[i] = 0;
        no = no->getProx();
    }

    int nivel;
    No* pai = nullptr;
    no = getNo(id_inicial);

    outputFile << "BUSCA EM PROFUNDIDADE A PARTIR DO NO " << id_inicial << endl << endl;


    if(no != nullptr)
    {
        depthFirstSearchFFile(no,vetor_coloracao,pai,0,outputFile);
    }
    else
    {
        outputFile << "NO NAO ENCONTRADO" << endl;
        return false;
    }

    delete [] vetor_coloracao;
    return true;
}

void Grafo::depthFirstSearchFFile(No* no, bool* vetor_coloracao, No* pai, int nivel,fstream &outputFile)
{
    if(no == nullptr)
        return;

    if(nivel == 0)
    {
        outputFile << "NO: " <<  no->getId() << " PAI: NULL NIVEL: " << nivel << endl;
    }
    else
    {
        outputFile << "NO: " <<  no->getId() << " PAI: " << pai->getId() << " NIVEL: " << nivel << endl;
    }

    vetor_coloracao[no->getI()] = 1;
    Aresta* aresta = no->getPrimeiraAresta();

    while(aresta != nullptr)
    {
        No* aux = getNo(aresta->getId_Alvo());
        if(vetor_coloracao[aux->getI()] == 0)
            depthFirstSearchFFile(aux,vetor_coloracao,no,nivel+1,outputFile);
        aresta = aresta->getProxAresta();
    }
}

void Grafo::breathFirstSearch()
{
    queue<No*> fila; //FILA

    No* no = this->primeiro_no; //PRIMEIRO NO DO GRAFO

    bool* visitado = new bool[this->ordem]; //VETOR DE MARCAÇÃO

    for(int i = 0; i < this->ordem && no != nullptr; i++)
    {
        visitado[i] = false;
        no->setI(i);
        no = no->getProx();
    }

    no = this->primeiro_no; //VOLTAMOS PARA O PRIMEIRO NO DO GRAFO
    visitado[no->getI()] = 1;

    fila.push(no);

    No* aux;
    Aresta* aresta;

    cout << "BUSCA EM LARGURA " << endl << endl;

    while(!fila.empty())
    {
        aux = fila.front();
        fila.pop();
        aresta = aux->getPrimeiraAresta();
        cout << aux->getId() << ", ";

        while(aresta != nullptr)
        {
            No* no_aux = getNo(aresta->getId_Alvo());
            if(visitado[no_aux->getI()] == 0)
            {
                visitado[no_aux->getI()] = 1;
                fila.push(no_aux);
            }

            aresta = aresta->getProxAresta();
        }
    }
}

void Grafo::breathFirstSearchFile(fstream& output_file)
{
    queue<No*> fila; //FILA

    No* no = this->primeiro_no; //PRIMEIRO NO DO GRAFO

    bool* visitado = new bool[this->ordem]; //VETOR DE MARCAÇÃO

    for(int i = 0; i < this->ordem && no != nullptr; i++)
    {
        visitado[i] = false;
        no->setI(i);
        no = no->getProx();
    }

    no = this->primeiro_no; //VOLTAMOS PARA O PRIMEIRO NO DO GRAFO
    visitado[no->getI()] = 1;

    fila.push(no);

    No* aux;
    Aresta* aresta;

    output_file << endl << endl << "BUSCA EM LARGURA " << endl << endl;

    while(!fila.empty())
    {
        aux = fila.front();
        fila.pop();
        aresta = aux->getPrimeiraAresta();
        output_file << aux->getId() << ", ";

        while(aresta != nullptr)
        {
            No* no_aux = getNo(aresta->getId_Alvo());
            if(visitado[no_aux->getI()] == 0)
            {
                visitado[no_aux->getI()] = 1;
                fila.push(no_aux);
            }

            aresta = aresta->getProxAresta();
        }
    }
}
