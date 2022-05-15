#ifndef SD_LABS_GRAPH_ADJ_LIST_H
#define SD_LABS_GRAPH_ADJ_LIST_H

#include "stddef.h"

/**
 * Structura unui nod din lista de adiacenta (cu liste inlantuite)
 */
typedef struct nodeAdjList {
    size_t nodeId;             /**< ID-ul nodului */
    int cost;                  /**< Costul muchiei */
    struct nodeAdjList *next;  /**< Urmatorul vecin */
} nodeAdjList_t;

/**
 * Structura grafului reprezentat prin liste de adiacenta
 */
typedef struct graphAdjList {
    size_t numNodes;           /**< Numarul de noduri din graf */
    nodeAdjList_t **adjList;   /**< Lista de adiacenta */
} graphAdjList_t;

/**
 * Structura unei muchii din graf
 */
typedef struct graphEdge {
    size_t u;       /**< Nodul sursa */
    size_t v;       /**< Nodul destinatie */
    int cost;       /**< Costul muchiei */
} graphEdge_t;

/**
 * @brief Functie care initializeaza un graf cu matrice de adiacenta. Initial,
 * toate elementele matricii vor avea valoarea 0
 *
 * @param numNodes numarul de noduri din graf
 *
 * @return graful initializat
 */
graphAdjList_t *initGraph(size_t numNodes);

/**
 * @brief Functie care insereaza o noua muchie in graful directionat ponderat
 *
 * @param g graful in care se face inserarea
 * @param u nodul de la care se pleaca
 * @param v nodul la care se ajunge
 * @param cost costul muchiei
 */
void insertEdge(graphAdjList_t *g, size_t u, size_t v, int cost);

/**
 * @brief Functie care sterge o muchie din graf
 *
 * @param g graful din care se sterge muchia
 * @param u nodul de la care se pleaca
 * @param v nodul la care se ajunge
 */
void removeEdge(graphAdjList_t *g, size_t u, size_t v);

/**
 * @brief Functie care returneaza numarul de muchii care au ca destinatie nodul dat
 *
 * @param g graful in care se afla nodul
 * @param u nodul pentru care se doreste sa se afle gradul intern
 *
 * @return gradul intern al nodului (deg-)
 */
size_t getInDegree(graphAdjList_t *g, size_t u);

/**
 * @brief Functie care returneaza numarul de muchii care au ca sursa nodul dat
 *
 * @param g graful in care se afla nodul
 * @param u nodul pentru care se doreste sa se afle gradul extern
 *
 * @return gradul extern al nodului (deg+)
 */
size_t getOutDegree(graphAdjList_t *g, size_t u);

/**
 * @brief Functie care verifica daca 2 noduri sunt vecine
 *
 * @param g graful in care se face cautarea
 * @param u nodul sursa
 * @param v nodul destinatie
 *
 * @return
 *      - 1 daca exista muchia (u, v)
 *      - 0 altfel
 */
int isNeighbour(graphAdjList_t *g, size_t u, size_t v);

/**
 * @brief Functie care returneaza vecinii nodului dat
 *
 * @param g graful in care se face cautarea
 * @param u nodul sursa
 *
 * @return lista de vecini in format (nod_sursa, nod_destinatie, cost)
 */
graphEdge_t **getNeighbours(graphAdjList_t *g, size_t u);

/**
 * @brief Functie care elibereaza memoria ocupata de lista de vecini
 *
 * @param edgeList lista de vecini
 */
void freeNeighboursList(graphEdge_t **edgeList);

/**
 * @brief Functie care elibereaza memoria ocupata de graf si il seteaza la NULL
 *
 * @param g graful
 */
void freeGraph(graphAdjList_t **g);

/**
 * @brief Functie care afiseaza vecinii unui nod
 *
 * @param neighbours lista de vecini
 */
void printNeighbours(graphEdge_t **neighbours, size_t u);

/**
 * @brief Functie care afiseaza lista de adiacenta a grafului
 *
 * @param g graful
 */
void printGraph(graphAdjList_t *g);

/**
 * @brief Functie care returneaza costul muchiei (u,v)
 * 
 * @param g Graful
 * @param u Nodul sursa
 * @param v Nodul destinatie
 * @return Costul
 */
int getCost(graphAdjList_t *g, int u, int v);

#endif //SD_LABS_GRAPH_ADJ_LIST_H
