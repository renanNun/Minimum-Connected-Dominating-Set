#include "No.h"

/*
* Construtor classe No para casos não ponderados, recebe apenas o Id do Nó a ser criado
* @param: Int id // identificador do Nó a ser criado
*/
No::No(int id)
{
    this->id = id;
    this->peso = 0;
    this->grau_de_entrada = 0;
    this->grau_de_saida = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->prox = nullptr;
    this->pai = id;
}
/*
* Construtor classe No para casos ponderados, recebe o Id do Nó a ser criado e o peso desse Nó
* @param: Int id // identificador do Nó a ser criado
* @param: Int peso// inteiro que representa o peso do Nó
*/
No::No(int id,int peso)
{
    this->id = id;
    this->peso = peso;
    this->grau_de_entrada = 0;
    this->grau_de_saida = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->prox = nullptr;
    this->pai = id;
}
/*
* Destrutor
*/
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
/*
* Função para inserir arestas entre o Nó que chama a função até o Nó com "id_alvo" e com a aresta tendo peso passado
* @param: Int id_alvo // identificador do Nó que receberá a aresta
* @param: Int peso// inteiro do peso da aresta, passar -1 para arestas não ponderadas
*/
void No::inserirAresta(int id_alvo,int peso)
{
    if(this->primeira_aresta != nullptr)
    {
        Aresta* aresta = new Aresta(id_alvo,this->id,peso);
        this->ultima_aresta->setProxAresta(aresta);
        this->ultima_aresta = aresta;
    }
    else
    {
        this->primeira_aresta = new Aresta(id_alvo,this->id,peso);
        this->ultima_aresta = this->primeira_aresta;
    }
}
/*
* Função para remover todas as arestas do Nó
*/
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
/*
* Função que verifica a existencia da aresta na lista de arestas
* @param: Int id_alvo // identificador do Nó que será verificado
* @return: booleano que representa a existencia da aresta com o Id_alvo
*/
bool No::existeAresta(int id_alvo)
{
    if(this->primeira_aresta != nullptr)
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
            if(aux->getId_Alvo() == id_alvo)
                return true;
    return false;
}
/*
* Função que remove uma aresta especifica e atualiza as informações de entrada e saida.
* @param: Int id // identificador do Nó que será verificado
* @param: bool direcionado // identificador do Nó que será verificado
* @param: No* no_alvo // identificador do Nó que será verificado
* @return: inteiro que representa se a aresta foi removida
*/
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
        {
            anterior->setProxAresta(aux->getProxAresta());
            cout << "CASO 1" << endl;
            cout << "id " << aux->getProxAresta()->getId_Alvo() << endl;
        }

        else
        {
            cout << "CASO 2" << endl;
            this->primeira_aresta = aux->getProxAresta();
            cout << "id " << aux->getProxAresta()->getId_Alvo() << endl;
        }


        if(aux == this->ultima_aresta)
            this->ultima_aresta = anterior;

        if(aux->getProxAresta() == this->ultima_aresta)
            this->ultima_aresta = aux->getProxAresta();

        delete aux;

        if(direcionado)
            this->diminuiGrauSaida();
        else
        {
            this->diminuiGrauEntrada();
            no_alvo->diminuiGrauEntrada();
        }

        return 1;
    }

    return 0;
}
/*
* Função que incrementa em um o Grau de de entrada
*/
void No::aumentaGrauEntrada()
{
    this->grau_de_entrada++;
}
/*
* Função que incrementa em um o Grau de de saida
*/
void No::aumentaGrauSaida()
{
    this->grau_de_saida++;
}
/*
* Função que decrementa em um o Grau de de entrada
*/
void No::diminuiGrauEntrada()
{
    if(this->grau_de_entrada > 0)
        this->grau_de_entrada--;
}
/*
* Função que decrementa em um o Grau de de entrada
*/
void No::diminuiGrauSaida()
{
    if(this->grau_de_saida > 0)
        this->grau_de_saida--;
}
/*
* Função que retorna a aresta entre o Nó que chama a função e o Nó que tenha o id passado
* @param: int id_alvo// id do Nó alvo
* @return: ponteiro para a aresta entre os os Nós,Null se ela não existe
*/
Aresta* No::getArestaEntre(int id_alvo)
{
    for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
        if(aux->getId_Alvo() == id_alvo)
            return aux;
    return nullptr;
}

/*
* Função que verifica a existencia de uma aresta entre o Nó chamdo e o No alvo.
* @param: int id_alvo// id do Nó alvo
* @return: booleano que representa a existencia da aresta entre os Nós indicados
*/
bool No::existeArestaEntre(int id_alvo)
{
    for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
        if(aux->getId_Alvo() == id_alvo)
            return true;
    return false;
}

// Getter e Setter iterador
int No::getI()
{
    return this->interador;
}

void No::setI(int i)
{
    this->interador = i;
}

//Funções para verificar conectividade

// Getters e setter da variavel marca usada para verificar conectividade do Grafo

bool No::getMarca()
{
    return marca;
}
void No::Marca()
{
    marca=true;
}
void No::desmarca()
{
    marca=false;
}
// Getter e setter Peso especial
int No::getPesoEspecial()
{
    return this->pesoEspecial;
}
void No::setPesoEspecial(int i)
{
    this->pesoEspecial=i;
}

//Funções Kruskal

// Getters e setter da variavel Pai que armazena o id de outro nó, usada no algoritmo de Kruskal
void No::setPai(int pai)
{
    this->pai= pai;
}

int No::getPai()
{
    return this->pai;
}
