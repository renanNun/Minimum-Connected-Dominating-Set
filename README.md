# Subconjunto mínimo dominante conexo

Este Repositório tem como objetivo implementar uma estrutura de armazenamento de grafos simples e suas respectivas operações possíveis.
Para mais detalhes, veja nessa [wiki](https://github.com/renanNun/Minimum-independent-set-connected/wiki/Introdu%C3%A7%C3%A3o).

## Para a criação do executável

```
$ g++ *.cpp -o grafosGrupo20
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

### Sobre os arquivos de Entrada.

O Seguinte programa aceita entradas [.txt](https://pt.wikipedia.org/wiki/Arquivo_de_texto), com o seguinte formato

```
n
a b p
```

Onde *n* é o número de Nós. <br>
*a* e *b* são os nós de forma que a presença deles indique a ocorrência de uma aresta. <br>
*p* indica o peso no caso de grafos ponderados. <br>

exemplo de entrada:
```
3
0 1 1
1 2 2
0 2 3
```

Ele também aceita entradas do tipo [dat](https://www.tecmundo.com.br/internet/8937-o-que-sao-arquivos-dat-que-aparecem-em-algumas-pastas-do-windows-.htm#:~:text=A%20extens%C3%A3o%20DAT%20representa%20um,texto%2C%20entre%20v%C3%A1rios%20outros%20tipos.), que possuam o seguinte formato:

```
NumberOfNodes:
x 
Positions
p q
r s
t v
******************WEIGHTS*****************************
a
b
c
*****************CONNECTIONS**************** 
1 0 0 0
0 1 0 1
1 0 1 0
0 0 0 1
```
Onde *x* é o número de nós <br>
*Positions* indica as coordenadas dos pontos de forma de coordenadas cartesianas <br>
*Weights* indica os pesos dos nós <br>
*Connections* indica a matriz de adjacência do grafo <br>
