#include "Prim.h"
#define INT_MAX 9999999999

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

Prim::Prim(Grafo* grafo, int no_escolhido)
{
    this->grafo = grafo;
    noEscolhido = grafo->getNo(no_escolhido);
    preencheListaArestas(grafo->getPrimeiroNo());
    preencheListaNos(grafo->getPrimeiroNo());
    gerar();
}

Prim::~Prim()
{

}

void Prim::preencheListaArestas(No* noInicial)
{
    int idAresta=0;
    list<Aresta* >  listaArestasAux; // Lista auxiliar para pegar todas as arestas

    //função que percorre o grafo, nomeia as arestas e salva ponteiros dela
    for (No *i= noInicial; i != nullptr; i = i->getProx())
    {
        for(Aresta* j= i->getPrimeiraAresta(); j!=nullptr; j=j->getProxAresta())
        {
            j->setIdAresta(idAresta);
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

void Prim::preencheListaNos(No* noInicial)
{

    for (No *i=noInicial; i!=nullptr; i=i->getProx())
    {
        grafoPrim.inserirNo(i->getId());
    }
}

Grafo Prim::gerar()
{
    No* no = noEscolhido;
    list<Aresta*> listaArestasAux;

    for(Aresta* & arestaAux : listaArestas)
    {
        if(arestaAux->getId_Origem() == no->getId())
            listaArestasAux.push_back(arestaAux);
    }


    Aresta* arestaAux;
    while(!listaArestasAux.empty())
    {
        arestaAux= listaArestasAux.front();
        listaArestasAux.pop_front();
        if(arestaAux->getId_Origem() == no->getId())
        {
            grafoPrim.inserirAresta(no->getId(),arestaAux->getId_Alvo(),arestaAux->getPeso());
        }
    }

    cout << grafoPrim.imprimir();
    return grafoPrim;
}

/*
void Prim::ordenar(Aresta **a,int n)
{

    int i, loc, j, k;
    Aresta *selected=nullptr;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];
        // find location where selected sould be inseretd
        loc = binarySearch(a, selected, 0, j);
        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = selected;
    }
}

int Prim::binarySearch(Aresta **a, Aresta *item, int low, int high)
{
    if (high <= low)
    {
        return (item->getPeso() > a[low]->getPeso())?  (low + 1): low;
    }


    int mid = (low + high)/2;
    if(item->getPeso() == a[mid]->getPeso())
    {
        return mid+1;
    }

    if(item->getPeso() > a[mid]->getPeso())
    {
        return binarySearch(a, item, mid+1, high);
    }

    return binarySearch(a, item, low, mid-1);
}

Grafo * Prim::gerar(int *soma)
{


    Grafo *h = new Grafo(0,false,true,false); // Cria-se o grafo que irá receber as arestas encontradas por 'auxKruskal'.

    Aresta **listaPrim = prim();
    *soma = 0;
    for(int i = 0; i < grafo->getOrdem()-1; i++)   // Cria em 'h' as arestas com as mesmas características das presentes em 'arestasAGM'.
    {
        Aresta *w = listaPrim[i];
        //cout << w << " " << w->getNoAdj() << " " << w->getOrigem() << " " << w->getPeso() << endl;

        int origem = w->getId_Origem();
        int fim = w->getId_Alvo();
        int peso = w->getPeso();




        if(origem != fim)
        {
            (*soma) += peso;
            h->inserirAresta(origem, fim, peso);
            h->setOrdem(h->getOrdem()+1);

        }

    }
    return h;
}


Aresta** Prim::prim()
{

    No *noAtual=NULL;
    int aux;
    int tamSolucao=0;
    int cont=0;
    noAtual=grafo->getPrimeiroNo();
    Aresta **primVet=new Aresta*[grafo->getOrdem()];
    Aresta *arestaAdj=NULL;
    Aresta **arestaVet=new Aresta*[grafo->getOrdem()];

    No *p = grafo->getPrimeiroNo();
    while(p != NULL)
    {
        p->desmarca();
        p = p->getProx();
    }

    while(noAtual->getMarca()==false&&tamSolucao<grafo->getOrdem()-1)
    {

        arestaAdj=noAtual->getPrimeiraAresta();//recebeu uma lista de arestas adjacentes

        for(Aresta *w=arestaAdj; w!=nullptr; w=w->getProxAresta())
        {
            if(tamSolucao==0) //primeira vez que for inserir no vetor de arestas adjacentes
            {
                arestaVet[cont]=new Aresta(w->getId_Alvo(),w->getId_Origem(),w->getPeso());
                cont++;
            }
            else //evitar a formação de ciclos
            {
                for(aux=0; aux<cont&&grafo->getNo(arestaVet[aux]->getId_Alvo())!=grafo->getNo(w->getId_Alvo()); aux++); //verificar se o nó adjacente da lista de arestaAdj já foi inserido como nó adjacente da solução primVet
                if(aux==cont) //percorreu e não encontrou no adjacente igual ao da arestaVet
                {
                    arestaVet[cont]=new Aresta(w->getId_Alvo(),w->getId_Origem(),w->getPeso());
                    cont++;
                }
                else
                {
                    if(arestaVet[aux]->getPeso()>w->getPeso()) //se uma aresta com o nó adjacente a um já pertencente ao vetor arestaVet tiver peso menor a aresta do vetor arestaVet, faço a substituição
                    {
                        arestaVet[aux]=new Aresta(w->getId_Alvo(),w->getId_Origem(),w->getPeso());
                    }
                }
            }
        }

        this->ordenar(arestaVet,cont);
        //cout << "ORDENHAMOS " << cont << endl;
        if(grafo->getNo(arestaVet[0]->getId_Alvo())->getMarca()==true) //se a menor aresta já foi inserida, verifica a possibilidade de inserir até achar uma que ainda não tenha sido inserida, na lista de arestas de menor peso
        {
            //cout << "PROBLEM" << endl;
            for(aux=0; aux<tamSolucao && grafo->getNo(arestaVet[aux]->getId_Alvo())->getMarca()==true; aux++);
            primVet[tamSolucao]=arestaVet[aux];
            tamSolucao++;
            noAtual->Marca();
            noAtual=grafo->getNo(arestaVet[aux]->getId_Alvo());
            for(int i=aux; i < cont-1; i++)
            {
                arestaVet[i]=arestaVet[i+1];
            }
            cont--;
        }
        else
        {
            primVet[tamSolucao]=arestaVet[0];
            tamSolucao++;
            noAtual->Marca();
            noAtual=grafo->getNo(arestaVet[0]->getId_Alvo());
            for(int i=0; i<cont-1; i++)
            {
                arestaVet[i]=arestaVet[i+1];
            }
            cont--;
        }
    }
    /*
    for(int i = 0; i < tamSolucao; i++)
        cout << primVet[i]->getId_Origem() << "--->" << primVet[i]->getId_alvo() << " ";
    cout << endl;

return primVet;
}


Prim::Prim(Grafo *grafo)
{

    this->grafo = grafo;
}

Prim::~Prim() {}
*/
