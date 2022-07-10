#ifndef __functions__
#define __functions__
#include "graph.h"
#include "utils.h"

/**
 * @brief Functia care rezolva taskul 1
 * 
 * Metoda de rezolvare:
 * - Algoritmul Floyd-Warshall pentru gasirea costurilor minime intre
 *   fiecare nod
 * 
 * - Ne folosim si de o matrice next pentru a retine pentru fiecare nod
 *   urmatorul nod din traseul de cost minim
 * 
 * @param G Graful
 */
void solve_e1(graph G);

/**
 * @brief Functia care rezolva taskul 2
 * 
 * Metoda de rezolvare:
 * - Ne vom folosi de 2 vectori (s si d) pentru a verifica daca nodul j va face
 *   parte din componenta conexa, construind vectorul s facand dfs extern din nod
 *   iar vectorul d facand dfs intern.
 * - Vectorul ctc ne spune din ce componenta conexa face parte nodul j
 * 
 * @param G Graful
 */
void solve_e2(graph G);

/**
 * @brief Functia care rezolva taskul 3
 * 
 * Metoda de rezolvare:
 * - Ne folosim de algoritmul lui djikstra pe masti si verificam drumul minim 
 *   in fiecare zona plecand din fiecare depozit
 * 
 * @param G Graful
 */
void solve_e3(graph G);

#endif