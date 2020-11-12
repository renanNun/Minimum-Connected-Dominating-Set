#Subconjunto mínimo dominante conexo

Repositorio que armazena uma estrutura de Grafos e disponibiliza a execução dos algoritmos :  Prim, Kruskal, Dijkstra, Floyd. Além disso uma implementação de um guloso e um guloso randomizado para o problema de subconjunto dominante minimo conexo.

Para executar o programa utilize:

Linux e MAC: g++ *.cpp -o <nome_do_executavel> <arquivo_de_entrada> <arquivo_de_saida>
Windows: 

O programa aceita arquivos .txt e .dat nos seguintes formatos:

.txt :
x //Numero de nos
X Y Z //Aresta De X Para Y Com Peso Z

exemplo:
3
0 1 1
1 2 2
0 2 3

.dat: 
NumberOfNodes:
x // colocar aqui numero de no
******************WEIGHTS***************************** // seguido do peso dos nos (tem que colocar o numero de peso igual ao numero de Nós declarados)
a
s
d
*****************CONNECTIONS**************** //Seguido da matriz de adjacencia
//Por exemplo
0 1 1
1 0 1 
1 1 0 

Exemplo:
NumberOfNodes:
3
******************WEIGHTS*****************************
1
2
3
*****************CONNECTIONS****************
0 1 1
1 0 1 
1 1 0

