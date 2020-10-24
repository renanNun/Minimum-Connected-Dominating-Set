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
}

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