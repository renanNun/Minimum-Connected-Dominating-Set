#include "Aresta.h"

Aresta::Aresta()
{

}

Aresta::Aresta(int id_alvo)
{
    this->id_alvo = id_alvo;
    this->prox = nullptr;
    this->peso = 0;
}

Aresta::Aresta(int id_alvo,int peso)
{
    this->id_alvo = id_alvo;
    this->prox = nullptr;
    this->peso = peso;
}

Aresta::Aresta(int id_alvo,int id_origem,int peso)
{
    this->id_alvo = id_alvo;
    this->id_origem = id_origem;
    this->prox = nullptr;
    this->peso = peso;
}

Aresta::~Aresta()
{
    if(this->prox != nullptr)
    {
        delete this->prox;
        this->prox = nullptr;
    }
}

/*Getters e Setters*/
int Aresta::getId_Alvo()
{
    return this->id_alvo;
}
int Aresta::getId_Origem()
{
    return this->id_origem;
}
int Aresta::getPeso()
{
    return this->peso;
}
Aresta* Aresta::getProxAresta()
{
    return this->prox;
}
void Aresta::setProxAresta(Aresta* aresta)
{
    this->prox = aresta;
}
void Aresta::setPeso(int peso)
{
    this->peso = peso;
}
void Aresta::setId_Origem(int novo_id_origem)
{
    this->id_origem = novo_id_origem;
}
void Aresta::setId_alvo(int novo_id_alvo)
{
    this->id_alvo = novo_id_alvo;
}