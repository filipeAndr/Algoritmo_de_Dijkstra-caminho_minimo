# Teoria dos Grafos e seus Algoritmos

## Informações do Estudante

- **Nome**: Filipe de Andrade Machado
- **Universidade**: Universidade Federal do Mato Grosso do Sul (FACOM - Faculdade de Computação)
- **Matéria**: Teoria dos Grafos e seus Algoritmos
- **Professor**: Vagner Pedrotti

## Algoritmo de Dijkstra sem fila de prioridade

Este projeto implementa o algoritmo de Dijkstra sem fila de prioridade. O algoritmo usa um vetor de distância e escolhe o vértice não visitado de menor valor no vetor por uma busca linear.

## Descrição do Projeto 

Usa-se simplesmente um vetor de distância e escolhe-se o vértice não visitado de menor valor no vetor por uma busca linear.

Neste Projeto, o problema do menor caminho é alterado para produzir o caminho de menor custo, mas em caso  de empate entre vários caminhos, deve-se optar pelo de menor comprimento, se ainda persistir o empate, deve-se optar pelo lexicograficamente anterior.

Para fazer isto, é preciso armazenar o comprimento do caminho encontrado para cada vértice: Comprimento[v], e fazer duas duas modificações:

No momento de selecionar o vértice v a ser fixado (e removido da lista dos pendentes). Quando se escolhe o vértice de menor valor de Distancia, em caso de empate, opte pelo com menor Comprimento. Em caso de persistência do empate, escolha o de menor número.

No momento de atualizar os vetores Distancia e Anterior. Quando se verifica se Distancia[v] + c(v,u) < Distancia[u], deve-se considerar o caso em que Distancia[v] + c(v,u) = Distancia[u]. Neste caso, deve-se trocar o antecessor de u para v caso Comprimento[v]+1 < Comprimento[u] ou Comprimento[v]+1 = Comprimento[u] e v for menor (numericamente) ao atual antecessor de u.

A implementação deve usar uma lista de adjacência para poder operar com grafos esparsos (muitos vértices e proporcionalmente poucas arestas).

O programa deverá processar a linha de comando, executar o que se pede, imprimindo a saída esperada e terminar.

### Como executar

Para executar o programa, você precisa ter o c instalado em seu computador.

Você pode executar o programa com o seguinte comando:

```bash
./menorcaminho grafo.txt s
```

### Como Compilar

```bash
gcc -Wall -pedantic *.c -g -o menorcaminho
```

Onde `grafo.txt` é o arquivo que contém a descrição do grafo e `s` é o vértice de origem.

## Formato do arquivo do grafo

O arquivo do grafo deve seguir o seguinte formato:

I n m  
N i g- g+  
E i j c T


Onde:

- `I n m`: Informações gerais do grafo, número de vértices e número de arestas.
- `N i g- g+`: Uma linha para cada vértice contendo o número do vértice de 0 a n-1 com o grau de entrada e o grau de saída.
- `E i j c`: Uma linha para cada arco do grafo, com o vértice de origem, vértice de destino e custo. O custo será sempre um inteiro não-negativo.
- `T`: Indica o fim do arquivo.

## Saída

Para todos os vértices (incluindo o próprio `s`) em ordem numérica, o programa imprime na saída uma linha contendo:

- Caso exista um caminho de `s` até `t`: `P t v c v1 v2 ... vn`
- Caso não exista caminho de `s` a `t`: `U t`
- Caso ocorra algum problema para leitura do grafo ou execução do algoritmo: `E`

