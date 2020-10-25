#include "No.h"

No::No(int id)
{
    this->id = id;
    this->peso = 0;
    this->grau_de_entrada = 0;
    this->grau_de_saida = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->prox = nullptr;
}

No::No(int id,int peso)
{
    this->id = id;
    this->peso = peso;
    this->grau_de_entrada = 0;
    this->grau_de_saida = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->prox = nullptr;
}

No::~No()
{
    Aresta* proxima_aresta = this->primeira_aresta;

    while(proxima_aresta != nullptr)
    {
        Aresta* aresta_auxiliar = proxima_aresta->getProxAresta();
        delete proxima_aresta;
        proxima_aresta = aresta_auxiliar;
    }

    free(proxima_aresta);
}

/*Getters e Setters*/
Aresta* No::getPrimeiraAresta()
{
    return this->primeira_aresta;
}

Aresta* No::getUltimaAresta()
{
    return this->ultima_aresta;
}

int No::getId()
{
    return this->id;
}

int No::getGrauEntrada()
{
    return this->grau_de_entrada;
}

int No::getGrauSaida()
{
    return this->grau_de_saida;
}

int No::getPeso()
{
    return this->peso;
}

No* No::getProx()
{
    return this->prox;
}

void No::setProxNo(No* no)
{
    this->prox = no;
}

void No::setPeso(int peso)
{
    this->peso = peso;
}

/*OUTROS MÉTODOS*/
void No::inserirAresta(int id_alvo,int peso)
{
    if(this->primeira_aresta != nullptr)
    {
        Aresta* aresta = new Aresta(id_alvo,this->id,peso);
        this->ultima_aresta->setProxAresta(aresta);
        this->ultima_aresta = aresta;
    } else {
        this->primeira_aresta = new Aresta(id_alvo,this->id,peso);
        this->ultima_aresta = this->primeira_aresta;
    }
}

void No::removerTodasArestas()
{
    if(this->primeira_aresta != nullptr)
    {
        Aresta* proxima = nullptr;
        Aresta* aux = this->primeira_aresta;

        while(aux != nullptr)
        {
            proxima = aux->getProxAresta();
            delete aux;
        }
    }

    this->primeira_aresta = this->ultima_aresta = nullptr;
}

bool No::existeAresta(int id_alvo)
{
    if(this->primeira_aresta != nullptr)
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
            if(aux->getId_Alvo() == id_alvo)
                return true;
    return false;
}

int No::removerAresta(int id, bool direcionado, No* no_alvo)
{
    if(this->existeAresta(id))
    {
        Aresta* aux = this->primeira_aresta;
        Aresta* anterior = nullptr;

        while(aux->getId_Alvo() != id)
        {
            anterior = aux;
            aux = aux->getProxAresta();
        }

        if(anterior != nullptr)
            anterior->setProxAresta(aux->getProxAresta());
        else
            this->primeira_aresta = aux->getProxAresta();

        if(aux == this->ultima_aresta)
            this->ultima_aresta = anterior;

        if(aux->getProxAresta() == this->ultima_aresta)
            this->ultima_aresta = aux->getProxAresta();

        delete aux;

        if(direcionado)
            this->diminuiGrauSaida();
        else {
            this->diminuiGrauEntrada();
            no_alvo->diminuiGrauEntrada();
        }

        return 1;
    }

    return 0;
}

void No::aumentaGrauEntrada()
{
    this->grau_de_entrada++;
}
void No::aumentaGrauSaida()
{
    this->grau_de_saida++;
}
void No::diminuiGrauEntrada()
{
    if(this->grau_de_entrada > 0)
        this->grau_de_entrada--;
}
void No::diminuiGrauSaida()
{
    if(this->grau_de_saida > 0)
        this->grau_de_saida--;
}

Aresta* No::getArestaEntre(int id_alvo)
{
    for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
        if(aux->getId_Alvo() == id_alvo)
            return aux;
    return nullptr;
}
bool No::existeArestaEntre(int id_alvo)
{
    for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
        if(aux->getId_Alvo() == id_alvo)
            return true;
    return false;
}

int No::getI()
{
    return this->interador;
}

void No::setI(int i)
{
    this->interador = i;
}
