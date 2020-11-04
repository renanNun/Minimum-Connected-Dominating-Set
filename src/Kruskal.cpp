#include "Kruskal.h"


Kruskal::Kruskal(Grafo *grafo)
{
    this->grafo = grafo;
    this->ordem = grafo->getOrdem();
    this->m = grafo->getNumeroArestas();
    this->direcional = grafo->getDirecionado();
    this->listaNos = grafo->getPrimeiroNo();


}
Kruskal:: ~Kruskal() {}

void Kruskal::vetorIdNos(int* idNos) // Função auxiliar que preenche o vetor com os ids dos nós da lista.
    {
        No *n;
        int i;
        for(n = listaNos, i = 0; n != nullptr; n = n->getProx(), i++)
        {
            idNos[i] = n->getId();
        }

    }

    int Kruskal::encontraIndice(int *idNos, int id) // Fun��o auxiliar que encontra a posi��o "i" de um id em um vetor idNos.
    {
        int i;
        for(i = 0; i < ordem; i++)
        {
            if(idNos[i] == id)
            {
                break;
            }
        }
        return i;
    }

    // Fun��o auxiliar que realiza a troca de posi��es entre valores dos vetores passados como par�metro.
    void Kruskal::troca(float *pesos, Aresta *conj, int i, int j)
    {
        float pAux = pesos[i];
        pesos[i] = pesos[j];
        pesos[j] = pAux;

        Aresta aAux = conj[i];
        conj[i] = conj[j];
        conj[j] = aAux;
    }

    // Fun��o auxiliar que retorna o �ndice da parti��o do QuickSort. Utiliza-se como piv� a �ltima posi��o do vetor.
    int Kruskal::particao(float *pesos, Aresta *conj, int inicio, int fim)
    {
        float pivo = pesos[fim];
        int i = inicio - 1;

        for(int j = inicio; j < fim; j++)
        {
            if(pesos[j] <= pivo)
            {
                i++;
                troca(pesos, conj, i, j);
            }
        }
        troca(pesos, conj, i + 1, fim);

        return (i + 1);
    }

    // Fun��o recursiva que implementa um QuickSort para fazer a ordena��o dos vetores passados como par�metro.
    void Kruskal::ordenaVetor(float *pesos, Aresta *conj, int inicio, int fim)
    {
        if(inicio < fim)
        {
            int indPart = particao(pesos, conj, inicio, fim);

            ordenaVetor(pesos, conj, inicio, indPart - 1);
            ordenaVetor(pesos, conj, indPart + 1, fim);
        }
    }


    // Função usada para encontrar o conjunto de arestas da arvore geradora mínima de um grafo.
    // Retorna a soma dos pesos das arestas desse conjunto.
    float Kruskal::auxKruskal(Aresta *arestasAGM)
    {
        if(direcional == false)
        {
            int cont = 0;
            bool verifica[ordem][ordem]; // Matriz auxiliar que será utilizada para que não haja repetição de arestas adicionadas a 'conjArestas'.
            Aresta conjArestas[m]; // Vetor que será preenchido com todas as arestas do grafo (conjunto de arestas candidatas a solução).
            int idNos[ordem]; // Vetor que será preenchido com os ids dos nós do grafo.
            vetorIdNos(idNos);
            float pesosArestas[m]; // Vetor que será preenchido com os pesos das arestas do grafo.

            Aresta *a;
            No *n;
            int i;

            for(int i = 0; i < ordem; i++)
            {
                for(int j = 0; j < ordem; j++)
                {
                    verifica[i][j] = false;
                }
            }

            int r = 0;
            for(i = 0, n = listaNos; i < ordem && n != nullptr; i++, n = n->getProx())   // Preenche 'conjArestas' com as arestas do grafo.
            {
                for(a = n->getAresta(); a!= nullptr; a = a->getProxAresta())
                {
                    int j = encontraIndice(idNos, a->getId_Alvo()); // Encontra �ndice do vetor 'idNos' correspondente ao id do n� adjacente � aresta em quest�o.

                    if(verifica[i][j] != true)   // Checa se a aresta j� se encontra em 'conjArestas'.
                    {
                        conjArestas[r] = *a; // Adiciona aresta a 'conjArestas'.
                        verifica[i][j] = true; // Marca na matriz auxiliar 'verifica' que a aresta entre os n�s da linha 'i' e coluna 'j' j� foi inserida em 'conjArestas'.
                        verifica[j][i] = true; // Aresta entre os n�s da linha 'i' e coluna 'j' equivale � aresta entre os n�s da linha 'j' e coluna 'i'.
                        r++; // Passar� para a pr�xima posi��o do vetor 'conjArestas'.
                    }
                }
            }

            for(int i = 0; i < m; i++)   // Preenche 'pesosArestas' com os pesos das arestas do grafo.
            {
                pesosArestas[i] = conjArestas[i].getPeso();
            }

            // Ordena em ordem crescente o vetor 'pesosArestas' e o vetor 'conjArestas'.
            ordenaVetor(pesosArestas, conjArestas, 0, m - 1);

            int comp[ordem]; // Vetor que indicar� a quais componentes conexas cada n� do grafo pertence (ao longo do processo).
            for(int i = 0; i < ordem; i++)   // Inicialmente, temos o n�mero de componentes conexas igual ao n�mero de n�s.
            {
                comp[i] = idNos[i];
            }

            i = 0;

            while(i < m && cont < ordem - 1)   // Preenche 'arestasAGM' com as arestas que formar�o a �rvore geradora m�nima do grafo.
            {
                int a = encontraIndice(idNos, conjArestas[i].getId_Origem());
                int b = encontraIndice(idNos, conjArestas[i].getId_Alvo());
                if(comp[a] != comp[b])   // Se os n�s pertencem a componentes conexas distintas, � poss�vel a adi��o da aresta � solu��o (pois n�o se formar� um ciclo).
                {
                    arestasAGM[cont] = conjArestas[i]; // Adiciona a aresta � solu��o.
                    cont++;
                    if(comp[a] < comp[b])   // N�s que pertencem � mesma componente ficam com o valor de id do n� de menor id da componente.
                    {
                        int t = comp[b];
                        comp[b] = comp[a];
                        for(int f = 0; f < ordem; f++)
                        {
                            if(comp[f] == t)
                            {
                                comp[f] = comp[a];
                            }
                        }
                    }
                    else
                    {
                        int p = comp[a];
                        comp[a] = comp[b];
                        for(int f = 0; f < ordem; f++)
                        {
                            if(comp[f] == p)
                            {
                                comp[f] = comp[b];
                            }
                        }
                    }
                }

                i++;
            }

            float somaPesos = 0.0;
            for(int c = 0; c < ordem - 1; c++)   // Soma os pesos das arestas que est�o na solu��o.
            {
                somaPesos += arestasAGM[c].getPeso();
            }

            return somaPesos;
        }

        return -1.0;
    }



    // Função que retorna o subgrafo correspondente a arvore geradora mínima do grafo.
    Grafo* Kruskal::gerar(float *soma)
    {
        Aresta arestasAGM[ordem - 1];
        *soma = auxKruskal(arestasAGM); // Chama a função 'auxKruskal' e encontra as arestas da árvore geradora mínima.

        Grafo *h = new Grafo(0,false,true,false); // Cria-se o grafo que irá receber as arestas encontradas por 'auxKruskal'.

        for(int i = 0; i < ordem - 1; i++)   // Cria em 'h' as arestas com as mesmas características das presentes em 'arestasAGM'.
        {
            int origem = arestasAGM[i].getId_Origem();
            int fim = arestasAGM[i].getId_Alvo();
            float peso = arestasAGM[i].getPeso();

            h->inserirNo(origem);
            h->inserirNo(fim);
            h->inserirAresta(origem, fim, peso);
            h->setOrdem(h->getOrdem()+1);
        }

        return h;
    }
