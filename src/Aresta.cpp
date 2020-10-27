#include "Aresta.h"

/*
* Construtor vazio da classe Aresta, inicia todos os parametros como null ou 0;
*/
Aresta::Aresta()
{
    this->id_alvo = -1;
    this->prox = nullptr;
    this->peso = 0;
}

/*
* Construtor  da classe Aresta para arestas Não ponderadas que armazena apenas um dos Nós
* @param: int id_alvo // id do Nó adjacente que será armazenado
*/
Aresta::Aresta(int id_alvo)
{
    this->id_alvo = id_alvo;
    this->prox = nullptr;
    this->peso = 0;
}

/*
* Construtor  da classe Aresta para arestas ponderadas que armazena um dos Nós e o peso da aresta
* @param: int id_alvo // id do Nó adjacente que será armazenado
* @param: int peso // peso da aresta
*/
Aresta::Aresta(int id_alvo,int peso)
{
    this->id_alvo = id_alvo;
    this->prox = nullptr;
    this->peso = peso;
}

/*
* Construtor  da classe Aresta para arestas ponderadas que armazena ambos os Nós,o de entra e o de saida, além do peso da aresta
* @param: int id_alvo // id do Nó adjacente que será armazenado
* @param: int id_origem // id do Nó de origem
* @param: int peso // peso da aresta
*/
Aresta::Aresta(int id_alvo,int id_origem,int peso)
{
    this->id_alvo = id_alvo;
    this->id_origem = id_origem;
    this->prox = nullptr;
    this->peso = peso;
}
/*
* Destrutor
*/
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
