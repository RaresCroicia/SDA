#include <stdio.h>
#include <stdlib.h>
#include "graph_adj_list.h"
#include "heap.h"
#include "priority_queue.h"

int all_visited(int *v, int n){
    for(int i = 0; i < n; i++)
        if(v[i] == 0)
            return 0;
    return 1;
}

graphAdjList_t* prim(graphAdjList_t *G, int nod_start){
    graphAdjList_t *arb = initGraph(G->numNodes);
    int *vis = calloc(G->numNodes, sizeof(int));
    heapArray_t *pQueue = NULL;
    vis[nod_start] = 1;
    graphEdge_t **neighbours = getNeighbours(G, nod_start);
    for(int idx = 0; neighbours[idx] != NULL; idx++)
        priorityEnqueue(&pQueue, neighbours[idx], sizeof(graphEdge_t), neighbours[idx]->cost);
    
    freeNeighboursList(neighbours);

    while(!isHeapEmpty(pQueue) || !all_visited(vis, G->numNodes)){
        pQueueItem_t *peek;
        priorityDequeue(&pQueue, peek);
        graphEdge_t *act = (graphEdge_t*)peek->data;
        printf("Se adauga in arbore muchia(%ld %ld %d)\n", act->u, act->v, act->cost);
        insertEdge(arb, act->u, act->v, act->cost);
        insertEdge(arb, act->v, act->u, act->cost);
        vis[act->v] = 1;
        neighbours = getNeighbours(G, act->v);
        for(int idx = 0; neighbours[idx] != NULL; idx++)
            if(!vis[neighbours[idx]->v])
                priorityEnqueue(&pQueue, neighbours[idx], sizeof(graphEdge_t), neighbours[idx]->cost);
        freeNeighboursList(neighbours);
    }
    freeHeap(&pQueue);
    return arb;
}

int main(void){
    // citire
    int n, m;
    fscanf(stdin, "%d%d", &n, &m);
    graphAdjList_t *G = initGraph(n);
    for(int i = 0; i < m; i++){
        int u,v,w;
        fscanf(stdin, "%d%d%d", &u, &v, &w);
        insertEdge(G, u, v, w);
        insertEdge(G, v, u, w);
    }
    graphAdjList_t *arb_acop = prim(G, 0);
    printGraph(arb_acop);

}