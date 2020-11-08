#include "Grafo.h"

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

void Grafo::aumentaNumArestas()
{
    this->numero_arestas++;
}


void Grafo::diminuiNumArestas()
{
    if(this->numero_arestas > 0)
        this->numero_arestas--;
}

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

bool Grafo::verificaAdjacencia(int i,int j)
{
    if(this->matriz_adjacencia[i][j])
        return true;
    return false;
}

void Grafo::adicionaArestaMatriz(int i,int j, int peso)
{
    matriz_adjacencia[this->getPosicaoMatriz(i)][this->getPosicaoMatriz(j)] = true;
    matriz_pesos[this->getPosicaoMatriz(i)][this->getPosicaoMatriz(j)] = peso;
}

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

int** Grafo::getMatrizPesos()
{
    return this->matriz_pesos;
}



void Grafo::traverse(No * u)
{
    u->Marca();
    for(No *v =primeiro_no; v=!nullptr; v=v->getProx())
    {

        if(v->existeArestaEntre(u->getId()))
        {
            if(!v->getMarca())
                traverse(v);
        }
    }
}

bool Grafo::ehConexo(Grafo * g)
{

    for (No *i= g->getPrimeiroNo(); i!=nullptr; i=i->getProx())
        i->desmarca();
    traverse(g->getPrimeiroNo())
    for (No *i= g->getPrimeiroNo(); i!=nullptr; i=i->getProx())
    {
        if (!i->getMarca())
        {
            return false
        }
    }
    return true
}


bool Grafo::ehCiclo()
{
    No* no = this->primeiro_no;
    bool* visitado = new bool[this->ordem];
    for(int i = 0; i < this->ordem; i++)
    {
        visitado[i] = false;
        no->setI(i);
    }

    no = this->primeiro_no;
    for(int i = 0; i < this->ordem && no != nullptr;i++)
    {
        if(!visitado[no->getI()])
            if(ehCicloAux(no,visitado,nullptr))
                return true;
        no = no->getProx();
    }
    return false;
}

bool Grafo::ehCicloAux(No* v,bool visitado[],No* pai)
{
    visitado[v->getI()] = true;
    No* aux;
    for(Aresta* adj = v->getPrimeiraAresta(); adj != nullptr; adj = adj->getProx())
    {
        aux = getNo(adj->getId_Alvo());
        if(!visitado[aux->getI()])
        {
            if(ehCicloAux(aux,visitado,v))
                return true;
        } else if(aux != pai)
            return true;
    }
    return false;
}
