#include "Kruskal.h"

/*
* Estrutura especial para ordenar lista de arestas pelo peso
* @param: Aresta* & Aresta1 // Ponteiro para primeira aresta
* @param: Aresta* & Aresta2 // ponteiro para a segnda aresta
* @return: boleeano que representa se o peso da primeira aresta é menor que o da segunda
*/

struct ListaArestaComparator
{
    // Compara 2 Arestas usando Peso
    bool operator ()( Aresta* & Aresta1,  Aresta* & Aresta2)
    {
        if(Aresta1->getPeso() == Aresta2->getPeso())
            return Aresta1 < Aresta2;
        return Aresta1->getPeso() < Aresta2->getPeso();
    }
};




/*
* Çonstrutor do Algoritmo que recebe um ponteiro de Grafo, armazena as informações pertinentes e chama o algoritmo
* @param: Aresta* & Aresta1 // Ponteiro para primeira aresta
* @param: Aresta* & Aresta2 // ponteiro para a segnda aresta
*/
Kruskal::Kruskal(Grafo *grafo)
{
    this->grafo = grafo;
    this->noInicial = grafo->getPrimeiroNo();
    algoritmo();
}

/*
* Destrutor
*/
Kruskal:: ~Kruskal() {}


/*
* Algoritmo do Kruskal
*/
void Kruskal::algoritmo()
{
    preencheListaArestas();
    preencheListaNos();
    pais();
    pesoSolucao=0;
    for(Aresta* & arestaAux : listaArestas)
    {
        if(!ehCiclo(arestaAux))
        {
            grafoKruskal.inserirAresta(arestaAux->getId_Origem(),arestaAux->getId_Alvo(),arestaAux->getPeso());
            pesoSolucao+=arestaAux->getPeso();
        }

    }

    imprime();
}


/*
* Função que preenche uma list com todas as arestas no grafo e ordena a lista
*/
void Kruskal::preencheListaArestas()
{

    int idAresta=0;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas

    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        for(Aresta* j= i->getPrimeiraAresta(); j!=nullptr; j=j->getProxAresta())
        {
            idAresta++;
            listaArestasAux.push_back(j);
        }
    }

    // Insere na lista final elementos que não se repetem (devido a implementação da aresta)
    int contador;
    for(Aresta* & arestaAux : listaArestasAux)
    {
        contador=0;
        for(Aresta* & arestaAux2 : listaArestas)
        {
            if(arestaAux2->getId_Alvo() == arestaAux->getId_Origem()
                    &&   arestaAux2->getId_Origem() == arestaAux->getId_Alvo())
                break;
            else
                contador++;
        }
        if(contador == listaArestas.size())
            listaArestas.push_front(arestaAux);
    }

    // Ordena lista de arestas em função do peso
    listaArestas.sort(ListaArestaComparator());
}

/*
* Função que insere todos os Nós no grafo solução
*/
void Kruskal::preencheListaNos()
{

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        grafoKruskal.inserirNo(i->getId());
    }
}

/*
* Função responsavel pela impressão da solução do algoritmo de Kruskal no arquivo de saida
* @param: fstream &outputFile // Arquivo onde será feita a impressão.
*/
void Kruskal::imprimeFile(fstream &outputFile)
{
    outputFile<< grafoKruskal.imprimir();
}

/*
* Função responsavel pela impressão da solução do algoritmo de Kruskal na tela
*/
void Kruskal::imprime()
{
    cout<< "Solução Kruskal: "<<endl;
    cout<<grafoKruskal.imprimir();
    cout<< "Peso final Solução : "<< pesoSolucao<<endl;
}

// Funções Do union find


/*
* Função que preenche todos os Nos como pais deles mesmo
*/
void Kruskal::pais()
{
    for (No * i = grafo->getPrimeiroNo() ; i!=nullptr; i=i->getProx())
    {
        i->setPai(i->getId());
    }
}

/*
* Função que acha a partição da qual o No faz parte, retornando o No raiz da partição
* @param: No * u // No que será feito a busca
* @return: No raiz da partição
*/

No *  Kruskal::acha(No * u)
{
    No * z = this->grafo->getNo(u->getPai());

    if(z == u)
    {
        return z;
    }
    else
    {
        return acha(z);
    }
}

/*
* Função que une duas partições diferentes
* @param: No * x // No que representa a primeira partição
* @param: No * y // No que representa a segunda partição
*/

void Kruskal::une(No *x, No *y)
{

    No * xraiz = acha(x);
    No * yraiz = acha(y);

    xraiz->setPai(yraiz->getId());

}

/*
* Função Verifica se a adição de uma aresta ao grafo cria um ciclo
* @param: Aresta * a // Aresta a ser verificada
* @return: boleeano que representa a existência do ciclo
*/

bool Kruskal::ehCiclo(Aresta * a)
{

    No * aux1 = grafoKruskal.getNo(a->getId_Origem());
    No * aux2 =  grafoKruskal.getNo(a->getId_Alvo());

    if(acha(aux1) == acha(aux2))
    {
        return true;
    }
    else
    {
        une(aux1,aux2);
    }
    return false;

}




