#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "graph_adj_matrix.h"

graphAdjMat_t *initGraph(size_t numNodes) {
    if (numNodes <= 0) {
        printf("initGraph: numarul de noduri trebuie sa fie un numar pozitiv nenul\n");
        return NULL;
    }

    graphAdjMat_t *g = malloc(sizeof(graphAdjMat_t));

    g->numNodes = numNodes;
    g->mat = malloc(numNodes * sizeof(int *));

    for (int i = 0; i < numNodes; i++) {
        g->mat[i] = calloc(numNodes, sizeof(int));
    }
    return g;
}


void insertEdge(graphAdjMat_t *g, size_t u, size_t v, int cost) {
    if (g == NULL) {
        printf("insertEdge: Graful este NULL\n");
        return;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("insertEdge: perechea de noduri (%lu, %lu) este invalida pentru un graf cu %lu noduri\n", u, v, g->numNodes);
        return;
    }

    if (isNeighbour(g, u, v)) {
        printf("Muchia (%lu, %lu) de cost %d exista deja in graf. Noul cost va fi %d\n", u, v, g->mat[u][v], cost);
    }

    /* Inserez noua muchie */
    g->mat[u][v] = cost;
}

void removeEdge(graphAdjMat_t *g, size_t u, size_t v) {
    if (g == NULL) {
        printf("removeEdge: Graful este NULL\n");
        return;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("removeEdge: perechea de noduri (%lu, %lu) este invalida pentru un graf cu %lu noduri\n", u, v, g->numNodes);
        return;
    }

    if (!isNeighbour(g, u, v)) {
        printf("removeEdge: Muchia (%lu, %lu) nu exista\n", u, v);
        return;
    }

    /* Sterg muchia */
    g->mat[u][v] = 0;
}

size_t getInDegree(graphAdjMat_t *g, size_t u) {
    if (g == NULL) {
        printf("getInDegree: Graful este NULL\n");
        return ULLONG_MAX;
    }

    if (u >= g->numNodes) {
        printf("getInDegree: nodul %lu nu exista intr-un graf cu %lu noduri\n", u, g->numNodes);
        return ULONG_MAX;
    }

    size_t inDegrees = 0;

    /* Incrementez contorul pentru fiecare valoarea nenula pe coloana lui 'u' */
    for (size_t v = 0; v < g->numNodes; v++) {
        if (g->mat[v][u] != 0) {
            inDegrees += 1;
        }
    }
    return inDegrees;
}

size_t getOutDegree(graphAdjMat_t *g, size_t u) {
    if (g == NULL) {
        printf("getOutDegree: Graful este NULL\n");
        return ULONG_MAX;
    }

    if (u >= g->numNodes) {
        printf("getOutDegree: nodul %lu nu exista intr-un graf cu %lu noduri\n", u, g->numNodes);
        return ULONG_MAX;
    }

    size_t outDegrees = 0;

    /* Incrementez contorul pentru fiecare valoarea nenula pe randul lui 'u' */
    for (size_t v = 0; v < g->numNodes; v++) {
        if (g->mat[u][v] != 0) {
            outDegrees += 1;
        }
    }
    return outDegrees;
}

int isNeighbour(graphAdjMat_t *g, size_t u, size_t v) {
    if (g == NULL) {
        printf("isNeighbour: Graful este NULL\n");
        return -1;
    }

    if (u >= g->numNodes || v >= g->numNodes) {
        printf("isNeighbour: perechea de noduri (%lu, %lu) este invalida pentru un graf cu %lu noduri\n", u, v, g->numNodes);
        return -1;
    }

    return g->mat[u][v] != 0;
}

graphEdge_t **getNeighbours(graphAdjMat_t *g, size_t u) {
    if (g == NULL) {
        printf("getNeighbours: Graful este NULL\n");
        return NULL;
    }

    graphEdge_t **neighbours = calloc(g->numNodes, sizeof(graphEdge_t *));
    size_t idx = 0;

    for (size_t v = 0; v <  g->numNodes; v++) {
        /* Adaug muchia in lista daca aceasta exista */
        if (isNeighbour(g, u, v)) {
            graphEdge_t *edge = malloc(sizeof(graphEdge_t));
            edge->u = u;
            edge->v = v;
            edge->cost = g->mat[u][v];

            neighbours[idx++] = edge;
        }
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

void freeGraph(graphAdjMat_t **g) {
    if (*g == NULL) {
        return;
    }

    /* Eliberez matricea de adiacenta */
    for (size_t u = 0; u < (*g)->numNodes; u++) {
        free((*g)->mat[u]);
    }
    free((*g)->mat);

    /* Eliberez structura */
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

void printGraph(graphAdjMat_t *g) {
    if (g == NULL) {
        printf("printGraph: Graful primit este NULL\n");
        return;
    }

    /* Afisez matricea de adiacenta */
    for (size_t u = 0; u < g->numNodes; u++) {
        for (size_t v = 0; v < g->numNodes; v++) {
            printf("%3d ", g->mat[u][v]);
        }
        printf("\n");
    }
    printf("\n");
}
