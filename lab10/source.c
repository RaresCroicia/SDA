#include <stdio.h>
#include <stdlib.h>
#include "graph_adj_list.h"
#define BIG 100000

void dfs(graphAdjList_t *G, int nod, int **visited, int **stack, int *head){
    (*visited)[nod] = 1;
    for(int i = 0; i < G->numNodes; i++){
        if(isNeighbour(G, nod, i) && !(*visited)[i])
            dfs(G, i, visited, stack, head);
    }
    (*stack)[*head] = nod;
    (*head)++;
}

void topological_sort_print(graphAdjList_t *G){
    int *stack = malloc(G->numNodes * sizeof(*stack));
    int *visited = malloc(G->numNodes * sizeof(*stack));
    for(int i = 0; i < G->numNodes; i++)
        visited[i] = 0;
    int head = 0;
    for(int i = 0; i < G->numNodes; i++)
        if(getInDegree(G, i) == 0){
            dfs(G, i, &visited, &stack, &head);
        }
    printf("Sortarea topologica a grafului G este: ");
    while(head > 0)
        printf("%d ", stack[--head]);
    printf("\n");
    free(stack);
    free(visited);
}

void shortest_Floyd(graphAdjList_t *G, int u, int v){
    if(u >= G->numNodes || v >= G->numNodes || u < 0 || v < 0){
        printf("Cel putin unul dintre noduri nu exista\n");
        return;
    }
    int **dist;
    dist = malloc(sizeof(int*) * G->numNodes);
    for(int i = 0; i < G->numNodes; i++)
        dist[i] = malloc(sizeof(int) * G->numNodes);
    
    for(int i = 0; i < G->numNodes; i++)
        for(int j = 0; j < G->numNodes; j++)
            dist[i][j] = BIG;

    for(int i = 0; i < G->numNodes; i++){
        dist[i][i] = 0;
        graphEdge_t **neighbours = getNeighbours(G, i);
        int idx = 0;
        while(neighbours[idx] != NULL){
            dist[i][neighbours[idx]->v] = neighbours[idx]->cost;
            idx ++;
        }
        freeNeighboursList(neighbours);
    }

    for(int k = 0; k < G->numNodes; k++)
        for(int i = 0; i < G->numNodes; i++)
            for(int j = 0; j < G->numNodes; j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    if(dist[u][v] == BIG){
        printf("Nu exista drum de la %d la %d\n", u, v);
        for(int i = 0; i < G->numNodes; i++)
            free(dist[i]);
        free(dist);   
        return;
    }
    printf("Drumul de cost minim dintre nodurile %d si %d este: %d\n", u, v, dist[u][v]);
    for(int i = 0; i < G->numNodes; i++)
        free(dist[i]);
    free(dist);   
}

void shortest_Bellman(graphAdjList_t *G, int src, int dest){
    int *dist;
    dist = calloc(G->numNodes, sizeof(int));
    for(int i = 0; i < G->numNodes; i++)
        dist[i] = BIG;
    dist[src] = 0;
    
    for(int k = 0; k < G->numNodes-1; k++)
        for(int i = 0; i < G->numNodes; i++){
            graphEdge_t **neighbours = getNeighbours(G, i);
            int idx = 0;
            while(neighbours[idx] != NULL){
                if(dist[i] != BIG && dist[i] + neighbours[idx]->cost < dist[neighbours[idx]->v])
                    dist[neighbours[idx]->v] = dist[i] + neighbours[idx]->cost;
                idx++;
            }
            freeNeighboursList(neighbours);
        }

    for(int i = 0; i < G->numNodes; i++){
        graphEdge_t **neighbours = getNeighbours(G, i);
            int idx = 0;
            while(neighbours[idx] != NULL){
                if(dist[i] != BIG && dist[i] + neighbours[idx]->cost < dist[neighbours[idx]->v]){
                    printf("Exista ciclu negativ!\n");
                    freeNeighboursList(neighbours);
                    return;
                }
                idx++;
            }
            freeNeighboursList(neighbours);
    }
    if(dist[dest] == BIG){
        printf("Nu exista drum de la %d la %d\n", src, dest);
        free(dist);
        return;
    }
    printf("Drumul de cost minim dintre nodurile %d si %d este: %d\n", src, dest, dist[dest]);
    free(dist);

}

void shortest_Dijkstra(graphAdjList_t *G, int src, int dest){
    int *found = calloc(G->numNodes + 1, sizeof(int));
    int *dist = calloc(G->numNodes + 1, sizeof(int));
    for(int i = 0; i < G->numNodes; i++){
        found[i+1] = 0;
        dist[i+1] = getCost(G, src, i);
    }
    found[src+1] = 1;
    dist[src+1] = 0;
    dist[0] = BIG;
    for(int k = 0; k < G->numNodes-1; k++){
        int pmax = 0;
        for(int i = 0; i < G->numNodes; i++)
            if(found[i+1] == 0 && dist[i+1] < dist[pmax])
                pmax = i+1;
        if(pmax > -1){
            found[pmax] = 1;
            for(int i = 0; i < G->numNodes; i++)
                if(found[i+1] == 0 && dist[i+1] > dist[pmax] + getCost(G, pmax-1, i))
                    dist[i+1] = dist[pmax] + getCost(G, pmax-1, i);
        }
    }
    if(dist[dest+1] == BIG){
        printf("Nu exista drum de la %d la %d\n", src, dest);
        free(dist);
        free(found);
        return;
    }
    printf("Drumul de cost minim dintre nodurile %d si %d este: %d\n", src, dest, dist[dest+1]);
    free(dist);
    free(found);
}


int main(void){
    int n_nodes, n_edges;
    fscanf(stdin, "%d%d", &n_nodes, &n_edges);
    graphAdjList_t *G = initGraph(n_nodes);
    for(int i = 0; i < n_edges; i++){
        int u, v, w;
        fscanf(stdin, "%d%d%d", &u, &v, &w);
        insertEdge(G, u, v, w);
    }
    topological_sort_print(G);
    printf("\nFLOYD:\n");
    shortest_Floyd(G, 0, 3);
    printf("\nBELLMAN:\n");
    shortest_Bellman(G, 0, 3);
    printf("\nDIJKSTRA\n");
    shortest_Dijkstra(G, 0, 3);
    freeGraph(&G);
}