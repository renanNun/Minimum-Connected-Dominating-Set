#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Grafo.h"
#include "Floyd.h"
#include "Dijkstra.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Guloso.h"

std::fstream inputFile;
std::fstream outputFile;

using namespace std;

void menu();

void limparTela();

Grafo* leitura();

Grafo* leituraDat();

string* limpaMatriz(string &line);

bool salvar();

int main(int argc, char * argv [])
{
    if(argc == 3)
    {
        inputFile.open(argv[1], ios::in); //Abre o Arquivo de Entrada
        outputFile.open(argv[2],ios::out); //Abre o Arquivo de Saida

        if(!inputFile)
        {
            cerr << "Erro ao Abrir o Arquivo de Entrada!" << endl;
            exit(-1);
        }

        if(!outputFile)
        {
            cerr << "Erro ao Abrir o Arquivo de Saida! " << endl;
            exit(-1);
        }
    }
    else
    {
        cerr << "O Algoritmo não localizou os arquivos de Entrada ou Saída!" << endl;
        cerr << "Verifique o Formato de entrada <nome_do_executavel> <arquivo_de_entrada> <arquivo_de_saida>" << endl;
        exit(-1);
    }

    cout << "\t\t\tTrabalho de Teoria dos Grafos" << endl;
    cout << "Alunos: Luan Reis Ciribelli e Renan Nunes da Costa Gonçalves" << endl;
    cout << "Nome do arquivo: " << argv[1] << endl;

    outputFile << "\t\t\tTrabalho de Teoria dos Grafos" << endl;
    outputFile << "Alunos: Luan Reis Ciribelli e Renan Nunes da Costa Gonçalves" << endl;
    outputFile << "Nome do arquivo: " << argv[1] << endl;

    Grafo* grafo;

    string arquivo = argv[1];
    string tex = "txt";
    bool flag = false;
    int k = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < arquivo.size(); j++)
            if(arquivo[j] == tex[i])
            {
                flag = true;
                k++;
            }
            else
            {
                flag = false;
            }
    }

    if(k == 3)
        flag = true;

    if(flag)
    {
        cout  << "LEITURA DE TXT " <<endl;
        grafo = leitura();
    }
    else
    {
        grafo = leituraDat();
    }


    outputFile << "Sobre o Grafo:" << endl;
    outputFile << "\tNumero de Vertices - " << grafo->getOrdem() << endl;
    outputFile << "\tNumero de Arestas - " << grafo->getNumeroArestas() << endl;
    outputFile << "\tGrau Medio - Por Adjacencia: " << grafo->grauMedioPorAdjacencia() << " | Por Somatorio: " << grafo->grauMedioPorSomatorio() << endl;
    outputFile << "\tFrequencia Relativa dos Graus: " << endl;
    for(int i = 0; i < grafo->grauDoGrafo(); i++)
    {
        outputFile << "\t\tGrau: " << i << " " << grafo->frequenciaRelativa(i) << ",";
    }
    outputFile << endl;


    cout << "Sobre o Grafo:" << endl;
    cout << "\tNumero de Vertices - " << grafo->getOrdem() << endl;
    cout << "\tNumero de Arestas - " << grafo->getNumeroArestas() << endl;
    cout << "\tGrau Medio - Por Adjacencia: " << grafo->grauMedioPorAdjacencia() << " | Por Somatorio: " << grafo->grauMedioPorSomatorio() << endl << endl;

    int opcao_escolhida;
    int id;

    /*Algoritmos de Caminho Mínimo e AGM*/
    Floyd* floyd;
    Dijkstra* dijkstra;
    Prim* prim;
    Kruskal* kruskal;
    Grafo* AGM;
    Guloso * guloso;

    while(true)
    {
        menu();
        cin >> opcao_escolhida;

        switch(opcao_escolhida)
        {
        case 0:
            outputFile.close();
            inputFile.close();
            exit(0);
            break;
        case 1:
            cout << grafo->imprimir();
            if(salvar())
            {
                outputFile << endl << grafo->imprimir() << endl;
            }
            limparTela();
            break;
        case 2:
            grafo->iniciaMatriz();
            cout << grafo->imprimirMatriz();
            if(salvar())
            {
                outputFile << endl << grafo->imprimirMatriz() << endl;
            }
            grafo->deleteMatriz();
            limparTela();
            break;
        case 3:
            cout << "\tNo Inicial: ";
            cin >> id;
            cout << endl;
            cout << grafo->depthFirstSearch(id);
            if(salvar())
            {
                outputFile << endl << grafo->depthFirstSearchFile(id,outputFile) << endl;
            }
            limparTela();
            break;
        case 4:
            grafo->breathFirstSearch();
            if(salvar())
            {
                grafo->breathFirstSearchFile(outputFile);
            }
            limparTela();
            break;
        case 5:
            if(!grafo->getPonderadoAresta())
            {
                cout << "Atenção: O grafo precisa ter aresta ponderada para Kruskal!" << endl;
                break;
            }
            else
            {
                cout << "\tNo Inicial: ";
                cin >> id;
                cout << endl;
                dijkstra = new Dijkstra(grafo,id);
                if(salvar())
                {
                    dijkstra->imprimeFile(outputFile);
                }
                limparTela();
                delete dijkstra;
            }
            break;
        case 6:
            if(!grafo->getPonderadoAresta())
            {
                cout << "Atenção: O grafo precisa ter aresta ponderada para Floyd!" << endl;
                break;
            }
            else
            {
                floyd = new Floyd(grafo);
                cout << endl << endl << "A EXECUTACAO DO ALGORITMO PODE RESULTAR NO FECHAMENTO IMEDIATO DO PROGRAMA" << endl;
                if(salvar())
                {
                    floyd->imprimeSolucaoFile(outputFile);
                }
                delete floyd;
                limparTela();
            }
            break;
        case 7:
            if(grafo->getDirecionado())
            {
                cout << "Atenção: O grafo não pode ser orientado para calcular a arvore geradora mínima por Prim!" << endl;
                break;
            }
            if(!grafo->getPonderadoAresta())
            {
                cout << "Atenção: O grafo precisa ter aresta ponderada para Prim!" << endl;
                break;
            }
            int escolha;
            cout<< "Escolha o no inicial de prim : "<<endl;
            cin >> escolha;
            while(escolha>(grafo->getOrdem()-1) || escolha<0)
            {
                cout<< "Escolha invalida, por favor escolha um no que exista: : "<<endl;
                cin >> escolha;
            }
            prim = new Prim(grafo,escolha);

            if(salvar())
            {
                prim->imprimeFile(outputFile);
            }
            limparTela();
            break;
        case 8:
            if(!grafo->getPonderadoAresta())
            {
                cout << "Atenção: O grafo precisa ter aresta ponderada para Kruskal!" << endl;
                break;
            }
            else
            {
                kruskal = new Kruskal(grafo);
                if(salvar())
                {
                    kruskal->imprimeFile(outputFile);
                }
                limparTela();
            }
            break;
        case 9:

            guloso= new Guloso(grafo);
            if(salvar())
            {
            }

            limparTela();
            break;
        default:
            cout << "Opcao Invalida! Digite Novamente: ";
            cin >> opcao_escolhida;
        }
    }

    delete grafo;
    return 0;
}

void menu()
{
    cout << "\t\tFuncionalidades:" << endl;
    cout << "[01] - Exibir Grafo por Lista de Adjacencia. " << endl;
    cout << "[02] - Exibir Grafo por Matriz de Adjacencia. " << endl;
    cout << "[03] - Busca Em Profundidade. " << endl;
    cout << "[04] - Busca Em Largura. " << endl;
    cout << "[05] - Algoritmo de Dijkstra. " << endl;
    cout << "[06] - Algoritmo de FloydMarshall. " << endl;
    cout << "[07] - Algoritmo de Prim. " << endl;
    cout << "[08] - Algoritmo de Kruskal. " << endl;
    cout << "[09] - Algoritmo de Guloso. " << endl;
    cout << "[0] - Sair. " << endl;
    cout << "Escolha: ";
}

void limparTela()
{
#ifdef LINUX
    system("clear");
#endif // LINUX
#ifdef _WIN32
    system("cls");
#endif // WIN32
}

bool salvar()
{
    char op = '\0';
    cout << endl << "Deseja salvar em arquivo? [s/n]" << endl;
    cin >> op;

    if(op == 's' || op != 'S')
        return true;
    else if(op == 'n' || op != 'N')
        return false;

    while(op != 's' || op != 'S' && op != 'n' || op != 'N')
    {
        cout << "Opcao Invalida! Digite Novamente: " << endl;
        cin >> op;
    }

    return false;
}

Grafo* leitura()
{
    bool direcionado = false;
    bool ponderado_aresta = true;
    bool ponderado_no = false;

    int id_no,id_alvo,peso;
    int ordem;
    string line;

    getline(inputFile,line);
    ordem = (stoi(line));

    Grafo* grafo = new Grafo(ordem,direcionado,ponderado_aresta,ponderado_no); //Devido as especificações do problema os indices de direcionado,ponderado aresta e nos estão travados

    if(!ponderado_aresta && !ponderado_no)
    {
        while(inputFile >> id_no >> id_alvo)
        {
            grafo->inserirAresta(id_no,id_alvo,0);
            if(!direcionado)
            {
                grafo->inserirAresta(id_alvo,id_no,0);
            }
            grafo->aumentaNumArestas();
        }
    }
    else if(ponderado_aresta && !ponderado_no)
    {
        while(inputFile >> id_no >> id_alvo >> peso)
        {
            grafo->inserirAresta(id_no,id_alvo,peso);
            if(!direcionado)
            {
                grafo->inserirAresta(id_alvo,id_no,peso);
            }
            grafo->aumentaNumArestas();
        }
    }

    return grafo;
}

string* limpaMatriz(string &line)
{
    int tam = (line.size()-1)/2;
    string* arr = new string[tam]; //Array para guardar os elementos
    int i = 0; //Controle
    stringstream ssin(line);
    while (ssin.good() && i < tam)
    {
        ssin >> arr[i];
        i++;
    }

    return arr;
}

Grafo* leituraDat()
{
    bool direcionado = false;
    bool ponderado_aresta = false;
    bool ponderado_no = false;
    int ordem;
    string line;
    string* control;
    getline(inputFile,line);
    if(line == "NumberOfNodes:")
    {
        getline(inputFile,line);
    }
    ordem = (stoi(line));

    bool matriz[ordem][ordem];

    Grafo* grafo = new Grafo(ordem,direcionado,ponderado_aresta,ponderado_no);

    /*Leitura propriamente dita*/
    while(line != "******************WEIGHTS*****************************")
    {
        getline(inputFile,line);
    }
    for(int i = 0; i < ordem; i++) //Cria todos os nós
    {
        getline(inputFile,line);
        grafo->inserirNo(i,stoi(line));
    }

    while(line != "*****************CONNECTIONS****************")
    {
        getline(inputFile,line);
    }

    for(int i = 1; i <= ordem; i++)
    {
        getline(inputFile,line);
        for(int j = i; j < ordem; j++)
        {
            control = limpaMatriz(line);
            if(stoi(control[j]) == 1)
            {
                grafo->inserirAresta(i-1,j-1,0);
                grafo->inserirAresta(j-1,i-1,0);
                grafo->aumentaNumArestas();
            }

        }
    }

    return grafo;
}
