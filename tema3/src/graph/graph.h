#ifndef __graph__
#define __graph__
#include "utils.h"

/**
 * @brief Structura nodului din graf (graful va fi salvat prin liste de adiacenta)
 * 
 */
typedef struct graphnode{
    int destination;
    double price;
    struct graphnode *next;
}graph_node;

/**
 * @brief Structura unui graf(salvam lista de adiacenta, depozitele si 
 *        cate noduri/depozite avem)
 * 
 */
typedef struct graph{
    graph_node **adj_list;
    int number_of_nodes, number_of_storages;
    int *storages;
}graph;

/**
 * @brief Functia de initializare a unui graf
 * 
 * @param no_nodes Numarul de noduri din graf
 * @param no_storages Numarul de depozite din graf
 * @return Graful
 */
graph init_graph(int no_nodes, int no_storages);

/**
 * @brief Functia de initiere a unui nod
 * 
 * @param j Nodul la care se leaga
 * @param cost Costul drumului
 * @return Nodul
 */
graph_node* init_node(int j, double cost);

/**
 * @brief Functia de adaugare a unui nod in graf
 * 
 * @param G Graful in care se adauga
 * @param i Nodul de la care pleaca legatura
 * @param j Nodul la care ajunge legatura
 * @param cost Costul legaturii
 */
void add_node(graph *G, int i, int j, double cost);

/**
 * @brief Functia care afiseaza elementele grafului
 * 
 * @param G Graful in sine
 */
void print_graph(graph G);

/**
 * @brief Functie care printeaza legaturile unui nod
 * 
 * @param G Graful
 * @param index Nodul
 */
void print_node_adj(graph G, int index);

/**
 * @brief Functia de eliberare a unui nod din graf
 * 
 * @param node Nodul
 */
void free_node(graph_node** node);

/**
 * @brief Functia de eliberare a unui graf
 * 
 * @param G Graful
 */
void free_graph(graph *G);

/**
 * @brief Functie care verifica daca exista muchie intre 2 noduri
 * 
 * @param G Graful 
 * @param i Nodul de la care se pleaca
 * @param j Nodul la care se ajunge
 * @param cost Costul care va fi transmis ca parametru in cazul in care exista muchie
 * @return Valoarea de adevar a existentei
 */
bool isEdge(graph G, int i, int j, double *cost);

/**
 * @brief Functie care verifica daca nodul este depozit
 * 
 * @param G Graful
 * @param node Nodul
 * @return Valoarea de adevar a existentei
 */
bool isStorage(graph G, int node);

/**
 * @brief Functia dfs extern
 * 
 * @param G Graful
 * @param node Nodul in care mergem in adancime
 * @param s Vectorul in care tinem minte daca am vizitat un nod
 */
void dfsE(graph G, int node, int **s);

/**
 * @brief Functia dfs intern
 * 
 * @param G Graful
 * @param node Nodul in care mergem in adancime
 * @param s Vectorul in care tinem minte daca am vizitat un nod
 */
void dfsI(graph G, int node, int **s);

/**
 * @brief Functia care aplica algoritmul Floyd Marshall pe un graf
 * 
 * @param G Graful
 * @param dist Matricea distantelor intre noduri
 * @param next Matricea care retine cine e urmatorul nod in traseu
 */
void Floyd(graph G, double ***dist, int ***next);

/**
 * @brief Functia care afiseaza drumul de cost minim
 * 
 * @param G Graful
 * @param i Nodul de la care se pleaca
 * @param j Nodul la care se ajunge
 * @param next Matricea de ajutor a retinerii urmatorului pas
 */
void Path(graph G, int i, int j, int **next);

/**
 * @brief Functia care aplica algoritmul lui djikstra pe zona data
 * 
 * @param G Graful
 * @param storage_index Depozitul de la care se pleaca
 * @param houses Vectorul de case la care trece curierul
 * @param n_h Numarul de case
 * @return Distanta minima
 */
double djikstra(graph G, int storage_index, int* houses, int n_h);
#endif