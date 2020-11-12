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
}

/*
* Construtor completo da classe Grafos,
* inicia todos os parametros recebidos
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
}
/*
* Destrutor
*/
Grafo::~Grafo()
{
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
}
/*
* Função que insere um Nó no grafo com o Id que foi passado e também insere o peso passado.
* @param: int Id// Id do nó a ser incluido
* @param:int peso // peso referente ao No
*/
void Grafo::inserirNo(int id,int peso)
{
    if(!existeNo(id))
    {
        if(this->primeiro_no != nullptr)
        {
            No* no = new No(id,peso);
            this->ultimo_no->setProxNo(no);
            this->ultimo_no = no;
        }
        else
        {
            this->primeiro_no = new No(id,peso);
            this->ultimo_no = this->primeiro_no;
        }
    }
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
* Função que faz busca em profundidade partindo do Nó com id passado imprimindo na saida
* @param: int id_inicial// parametro que representa o id do Nó em que a busca será iniciado
* @param: fstream &outputFile// caminho do arquivo que salva a impressão
* @return: busca em profundidade
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
/*
* Função auxiliar da busca em profundidade.
* @param: int id_inicial// parametro que representa o id do Nó em que a busca será iniciado
*/
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
/*
* Função que faz busca em largura imprimindo na saida
* @return: busca em Largura
*/
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
/*
* Função que faz busca em largura
* @param: fstream &outputFile// caminho do arquivo que salva a impressão
* @return: busca em Largura
*/
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

/*
* Função auxiliar para a função que verifica conectividade, ela percorre o grafo e marca os nos percorridos
* @param: No * u // No onde se começa a ser percorrido
*/
void Grafo::percorre(No * u)
{
    u->Marca();
    for(No *v = this->primeiro_no; v != nullptr; v = v->getProx())
    {
        if(v->existeArestaEntre(u->getId()))
        {
            if(!v->getMarca())
                percorre(v);
        }
    }
}
/*
* Função que verifica conectividade do Grafo
* @return: booleano referente a conectividade do grafo
*/
bool Grafo::ehConexo()
{
    No* primeiro = this->primeiro_no;
    for (No *i= this->primeiro_no; i!=nullptr; i=i->getProx())
        i->desmarca();
    percorre(primeiro);
    for (No *i= this->primeiro_no; i!=nullptr; i=i->getProx())
    {
        if (!i->getMarca())
        {
            return false;
        }
    }
    return true;
}

/*
* Função que cria a matriz na memoria
*/
void Grafo::alocaMatriz()
{
    this->matriz_adjacencia = new bool*[ordem];

    for(int i = 0; i < ordem; i++)
        matriz_adjacencia[i] = new bool[ordem];
}

/*
* Função que inicia a matriz com os valores
*/
void Grafo::iniciaMatriz()
{
    alocaMatriz();
    No* no = primeiro_no;

    for(int i = 0; i < ordem; i++)
    {
        no->setI(i);
        no = no->getProx();
    }
    int i;
    no = primeiro_no;
    while(no != nullptr) //Inicia a matriz com zeros
    {
        i = no->getI();
        for(int j = 0; j < ordem; j++)
        {
            matriz_adjacencia[i][j] = false;
        }

        no = no->getProx();
    }
    No* aux;
    for(no = primeiro_no; no != nullptr; no = no->getProx())
    {
        for(Aresta* a = no->getPrimeiraAresta(); a != nullptr; a = a->getProxAresta())
        {
            aux = getNo(a->getId_Alvo());
            matriz_adjacencia[no->getI()][aux->getI()] = true;
        }
    }
}

/*
* Função que deleta a matriz da memoria
*/
void Grafo::deleteMatriz()
{
    for(int i = 0; i < ordem; i++)
           delete [] matriz_adjacencia[i];
    delete [] matriz_adjacencia;
}
