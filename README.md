# Subconjunto mínimo dominante conexo

Este Repositório tem como objetivo implementar uma estrutura de armazenamento de grafos simples e suas respectivas operações possíveis.
Para mais detalhes, veja nessa [wiki](https://github.com/renanNun/Minimum-independent-set-connected/wiki/Introdu%C3%A7%C3%A3o).

## Para a criação do executável

```
$ g++ *.cpp -o grafosGrupo
```

## Para a execução do programa utiliza-se a seguinte linha de comando:

Para Mac e Linux

```
$ ./grafosGrupo20 <arquivo_de_entrada> <arquivo_de_saida>
```

Para o sistema Windows:

```
$ grafosGrupo20.exe <arquivo_de_entrada> <arquivo_de_saida>
```

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

