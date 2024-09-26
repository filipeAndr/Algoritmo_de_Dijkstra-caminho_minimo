#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>


// Definição da Estrura de dados:

typedef struct no *link;
struct no{ 
   int w; 
   int custo;
   link next; 
};

typedef struct grafo *Grafo;
struct grafo {
   int vertices; 
   int arestas; 
   link *adj; 
};

static link novoNo(int w, int custo, link next) { 
   link a = malloc( sizeof (struct no));
   a->w = w; 
   a->custo = custo;
   a->next = next;     
   return a;                         
}

Grafo inicializaGrafo(int V, int A) { 
   Grafo G = malloc( sizeof *G);
   G->vertices = V; 
   G->arestas = A;
   G->adj = malloc( V * sizeof (link));
   for (int v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

void grafoInsereArco( Grafo G, int v, int custo, int w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = novoNo( w, custo, G->adj[v]);
}

// Função Auxiliar de Inicialização:
void inicializaD(int vertices, int *dist, int *ant, int *compri,int s){
    for(int i = 0; i < vertices; i++){
        dist[i] = INT_MAX/2;
        ant[i] = -1;
        compri[i] = 0;
    }
    dist[s] = 0;
    ant[s] = s;
}

void printPath(int *ant, int j) {

    if (ant[j] == j) {
        return;
    }
    else{
        printPath(ant, ant[j]);
        printf("%d ", ant[j]);
    }
    
}

void imprimeCaminho(Grafo g, int *dist, int *comprimento, int *ant){
    int i;
    for(i = 0; i < g->vertices; i++){
        if((ant[i] == - 1) && (dist[i] == INT_MAX/2)){
            printf("U %i\n", i);
        }else{
            printf("P %i %i %i ", i, dist[i], comprimento[i]);
            printPath(ant, i);
            printf("%i \n", i);
        }
    }
}

void imprimeLink (link le) {
   link p;
   for (p = le; p != NULL; p = p->next)
      printf ("%d, Custo: %i, ", p->w, p->custo);
}

void imprimeListaAdjacencia(Grafo g){
    for(int i = 0; i < g->vertices; i++){
        printf("%i -> ", i);
        imprimeLink(g->adj[i]);
        printf("\n");
    }
}

// Varre o vetor de vertices abertos e se encontrar um aberto ele retorna
bool existeAberto(Grafo g, bool *aberto){

    for(int i = 0; i < g->vertices; i++){
        if(aberto[i]){
            return(true);
        }
    }
    return(false);
}

int menorDist(Grafo g, bool *aberto, int *dist, int *comprimento){

    // Varre e pega o indice do menor aberto
    int i;
    for(i = 0; i < g->vertices; i++){ 
        if(aberto[i]){
            break;
        }
    }

    // Varreu e não encontrou nada retorna (-1)
    if(i == g->vertices) return(-1);

    int menor = i;
    for(i = menor+1; i < g->vertices; i++){

        if(aberto[i]){
            if((dist[menor] > dist[i])){
                menor = i;
            }
            else if(dist[menor] == dist[i]){
                if(comprimento[menor] > comprimento[i]){
                    menor = i;
                }
            }    
        }
    }
    //printf("menor: %i\n", menor);
    return(menor);
}

void relaxa(Grafo g, int *dist, int *ant, int u, int *compri){
    link adj = g->adj[u];

    // Visita todos os vizinhos de u
    while(adj){
        int v = adj->w;

        // se o custo + dist[u] < dist[v] troca a distancia
        if(dist[v] > dist[u] + adj->custo){
            dist[v] = dist[u] + adj->custo;
            ant[v] = u;
            compri[v] = compri[u] + 1;
        }

        // se for igual usa o critério do caminho com menor comprimento
        else if(dist[v] == dist[u] + adj->custo){

            // se empatar o comprimento do caminho, pegue o vértice menor em questão numérica
            if((compri[u] + 1 < compri[v]) || ((compri[u] + 1 == compri[v]) && u < ant[v])){
                dist[v] = dist[u] + adj->custo;
                compri[v] = compri[u] + 1;
                ant[v] = u;
            }
        }
        
        adj = adj->next;
    }
}

void dijkstra(Grafo grafo, int s){
    
    // Inicializações

    int dist[grafo->vertices];
    int ant[grafo->vertices];
    bool aberto[grafo->vertices];
    int comprimento[grafo->vertices];

    inicializaD(grafo->vertices, dist, ant, comprimento,s); 

    for(int i = 0; i < grafo->vertices; i++){ 
        aberto[i] = true;
    }

    // Enquanto houver vértice aberto:
    while(existeAberto(grafo, aberto)){

        // Escolha u cuja estimativa seja a menor dentre os abertos
        int u = menorDist(grafo, aberto, dist, comprimento); 
                
        // feche u
        aberto[u] = false;

        // relaxe a aresta (u, w)
        relaxa(grafo, dist, ant, u, comprimento);

    }
    // Imprime todas as distâncias
    imprimeCaminho(grafo, dist, comprimento, ant);

    /*
    printf("\nVetor de Anteriores:\n");
    for(int i = 0; i < grafo->vertices; i++){
        printf("%i ", ant[i]);
    }
    printf("\n");

    printf("\nVetor de Distancia:\n");
    for(int i = 0; i < grafo->vertices; i++){
        printf("%i ", dist[i]);
    }
    printf("\n");

     */

}//*/

void main(int args,char* argv[]){

    // Verifica se pelo menos um argumento foi passado
    if (args < 2) {printf("Nenhum argumento foi passado.\n");}

    //Crie um dado do tipo Arquivo
    FILE *grafos = fopen(argv[1], "r");
    char *caracteres = NULL;
    int tamanho1 = 0;

    char c;
    while ((c = fgetc(grafos)) != EOF) {

        // Alocar memória para o próximo caractere no vetor
        caracteres = (char *)realloc(caracteres, (tamanho1 + 1) * sizeof(char));

        if (c != '\n') { // ignorar quebra de linha

            if (caracteres == NULL) {
                printf("Erro ao alocar memória.\n");
            }

            // Armazenar o caractere no vetor
            caracteres[tamanho1] = c;
            tamanho1++;
        }
        else{
            // Adiciona espaço entre os valores
            caracteres[tamanho1] = ' ';
            tamanho1++;
        }
    }
    // Aloque memória para o vetor
    caracteres = (char *)realloc(caracteres, (tamanho1 + 1) * sizeof(char));
    caracteres[tamanho1] = '\0'; 

    // Use strtok para dividir a string em tokens e Cria a lista de Adjacência
    char *token = strtok(caracteres, " ");

    // Definições das vertiáveis e vetores
    int i[2], e[3];
    char verificacao;
    int contI = 0, contE = 0;

    Grafo grafo;
    bool grafoOk;

    // Laço que lê todos os tokens, inicializa o Grafo e constrói todos os arcos
    while (token != NULL) {
        if ((isdigit(token[0])) && (verificacao == 'I')) {

            // Use atoi para converter o token em um número e coloca-lo no vetor i[]
            int numero = atoi(token);
            i[contI] = numero;
            contI++;

            if(contI == 2){

                if(i[0] < 1000000 && i[1] < 10000000){

                    // se os Vertices e arestas não passarem do limite Inizializa
                    grafo = inicializaGrafo(i[0], i[1]);
                    grafoOk = true;
                    
                }else {

                    // Caso passe retorna E
                    grafoOk = false;
                    printf("E\n");
                    break;
                }
                
            }

        } else if ((isdigit(token[0])) && (verificacao == 'E')) {

            // Use atoi para converter o token em um número e coloca-lo no vetor e[]
            int numero = atoi(token);
            e[contE] = numero;
            contE++;
            
            if(contE == 3){

                // A cada volta Novo arco é acrescentado a lista de Adj
                grafoInsereArco(grafo, e[0], e[2], e[1]);
            }

        }else {
            // Para ver as letras é só usar %s
            contE = 0;
            verificacao = *token;
            
        }

        // Avance para o próximo token
        token = strtok(NULL, " ");
    }


    if(grafoOk){
        
        //printf("Lista de Adjacencia:\n\n");
        //imprimeListaAdjacencia(grafo);
        //printf("\n");

        // Converte o char S em inteiro e chama a função Dijkstra
        int s = atoi(argv[2]);
        dijkstra(grafo, s);

        
    }else{
        printf("E\n");
    }
    
    
    //Feche o Arquivo e libere os buffers
    free(caracteres);
    fclose(grafos);
}

