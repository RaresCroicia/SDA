#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph_adj_list.h"

graphAdjList_t *initGraph(size_t numNodes) {
    if (numNodes <= 0) {
        printf("initGraph: numarul de noduri trebuie sa fie un numar pozitiv nenul\n");
        return NULL;
    }

    graphAdjList_t *g = malloc(sizeof(graphAdjList_t));
    g->numNodes = numNodes;
    g->adjList = calloc(numNodes, sizeof(nodeAdjList_t *));

    return g;
}

void insertEdge(graphAdjList_t *g, size_t u, size_t v, int cost) {
    if (g == NULL) {
        printf("insertEdge: Graful este NULL\n");
        return;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("insertEdge: perechea de noduri (%lu, %lu) este invalida pentru un graf cu %lu noduri\n", u, v, g->numNodes);
        return;
    }

    nodeAdjList_t *aux = g->adjList[u];

    while (aux != NULL) {
        if (aux->nodeId == v) {
            printf("Muchia (%lu, %lu) de cost %d exista deja in graf. Noul cost va fi %d\n", u, v, aux->cost, cost);
            aux->cost = cost;
            return;
        }
        aux = aux->next;
    }

    /* Creez noul nod */
    nodeAdjList_t *neighbour = malloc(sizeof(nodeAdjList_t));
    neighbour->nodeId = v;
    neighbour->cost = cost;

    /* Inserez noul nod */
    neighbour->next = g->adjList[u];
    g->adjList[u] = neighbour;
}

void removeEdge(graphAdjList_t *g, size_t u, size_t v) {
    if (g == NULL) {
        printf("removeEdge: Graful este NULL\n");
        return;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("removeEdge: perechea de noduri (%lu, %lu) este invalida pentru un graf cu %lu noduri\n", u, v, g->numNodes);
        return;
    }

    if (g->adjList[u] == NULL) {
        printf("removeEdge: Nodul %lu nu are vecini\n", u);
        return;
    }

    nodeAdjList_t *aux = g->adjList[u];

    /* Primul element din lista e nodul cautat */
    if (g->adjList[u]->nodeId == v) {
        g->adjList[u] = aux->next;
        free(aux);
        return;
    }

    /* Caut vecinul in lista de adiacenta */
    while (aux != NULL) {
        if (aux->next != NULL && aux->next->nodeId == v) {
            nodeAdjList_t *del = aux->next;
            aux->next = del->next;
            free(del);
            return;
        }
        aux = aux->next;
    }
}

size_t getInDegree(graphAdjList_t *g, size_t u) {
    if (g == NULL) {
        printf("getInDegree: Graful este NULL\n");
        return ULLONG_MAX;
    }

    if (u >= g->numNodes) {
        printf("getInDegree: nodul %lu nu exista intr-un graf cu %lu noduri\n", u, g->numNodes);
        return ULONG_MAX;
    }

    size_t inDegree = 0;

    /* Verific cate noduri au o legatura catre nodul 'u' */
    for (size_t v = 0; v < g->numNodes; v++) {
        if (isNeighbour(g, v, u)) {
            ++inDegree;
        }
    }

    return inDegree;
}

size_t getOutDegree(graphAdjList_t *g, size_t u) {
    if (g == NULL) {
        printf("getOutDegree: Graful este NULL\n");
        return ULONG_MAX;
    }

    if (u >= g->numNodes) {
        printf("getOutDegree: nodul %lu nu exista intr-un graf cu %lu noduri\n", u, g->numNodes);
        return ULONG_MAX;
    }

    size_t outDegree = 0;
    nodeAdjList_t *aux = g->adjList[u];

    /* Verific la cate noduri se poate ajunge din nodul 'u' */
    while (aux != NULL) {
        ++outDegree;
        aux = aux->next;
    }

    return outDegree;
}

int isNeighbour(graphAdjList_t *g, size_t u, size_t v) {
    if (g == NULL) {
        printf("isNeighbour: Graful este NULL\n");
        return -1;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("isNeighbour: perechea de noduri (%lu, %lu) este invalida pentru un graf cu %lu noduri\n", u, v, g->numNodes);
        return -1;
    }

    nodeAdjList_t *aux = g->adjList[u];

    /* Caut vecinul in lista de adiacenta */
    while (aux != NULL) {
        if (aux->nodeId == v) {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

graphEdge_t **getNeighbours(graphAdjList_t *g, size_t u) {
    if (g == NULL) {
        printf("getNeighbours: Graful este NULL\n");
        return NULL;
    }

    graphEdge_t **neighbours = calloc(g->numNodes, sizeof(graphEdge_t *));
    size_t idx = 0;
    nodeAdjList_t *aux = g->adjList[u];

    /* Adaug toate muchiile care pornesc din nodul 'u' in lista de muchii */
    while (aux != NULL) {
        graphEdge_t *edge = malloc(sizeof(graphEdge_t));
        edge->u = u;
        edge->v = aux->nodeId;
        edge->cost = aux->cost;

        neighbours[idx++] = edge;
        aux = aux->next;
    }

    return neighbours;
}

void freeNeighboursList(graphEdge_t **edgeList) {
    size_t idx = 0;

    while (edgeList[idx] != NULL) {
        free(edgeList[idx]);
        ++idx;
    }
    free(edgeList);
}

void freeGraph(graphAdjList_t **g) {
    if (*g == NULL) {
        return;
    }

    nodeAdjList_t *aux;

    /* Eliberez listele de adiacenta pentru fiecare nod */
    for (size_t u = 0; u < (*g)->numNodes; u++) {
        while ((*g)->adjList[u] != NULL) {
            aux = (*g)->adjList[u];
            (*g)->adjList[u] = aux->next;
            free(aux);
        }
    }
    free((*g)->adjList);

    /* Eliberez structura grafului */
    free(*g);
    *g = NULL;
}

void printNeighbours(graphEdge_t **neighbours, size_t u) {
    if (neighbours == NULL) {
        printf("printNeighbours: Lista de vecini data este nula\n");
        return;
    }

    size_t idx = 0;

    printf("%lu: ", u);

    /* Afisez toate muchiile din lista de vecini pe cate o linie */
    while (neighbours[idx] != NULL) {
        printf("(%lu %d) ", neighbours[idx]->v, neighbours[idx]->cost);
        ++idx;
    }
    printf("\n");
}

void printGraph(graphAdjList_t *g) {
    if (g == NULL) {
        printf("printGraph: Graful este NULL\n");
        return;
    }

    for (size_t u = 0; u < g->numNodes; u++) {
        graphEdge_t **neighbours = getNeighbours(g, u);
        printNeighbours(neighbours, u);
        freeNeighboursList(neighbours);
    }
}

int getCost(graphAdjList_t *g, int u, int v){
    graphEdge_t **neighbours = getNeighbours(g, u);
    for(int idx = 0; neighbours[idx] != NULL; idx++)
        if(neighbours[idx]->v == v){
            int cost = neighbours[idx]->cost;
            freeNeighboursList(neighbours);
            return cost;
        }
    freeNeighboursList(neighbours);
    return 100000;
}