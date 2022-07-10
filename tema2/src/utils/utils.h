#ifndef __UTILS__
#define __UTILS__
#define TRUE 1
#define FALSE 0
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "rgb.h"
#include "tree.h"

typedef unsigned char bool;
/**
 * @brief Functie care verifica daca se primeste 'h' sau 'v' pentru parametrul -m
 * 
 * @param string Sirul/Litera verificata
 * @return carecterul este 'h' sau 'v'
 */
bool is_valid_for_m(char* string);

/**
 * @brief Patratul unui numar
 * 
 * @param a Numarul initial
 * @return Patratul acestuia
 */
int square(int a);

/**
 * @brief Calculeaza eroarea de culoare dintr-o anumita zona din matricea de pixeli
 * 
 * @param matrix Matricea de pixeli
 * @param startX Pozitia initiala de pe axa Ox
 * @param startY Pozitia initiala de pe axa Oy
 * @param width Latimea zonei
 * @param height Inaltimea zonei
 * @return Eroarea de culoare
 */
int64_t determinate_mean(RGB** matrix, int startX, int startY, int width, int height);

/**
 * @brief Creeaza matricea de pixeli in functie de arborele cuaternar
 * 
 * @param matrix Matricea care va fi creata
 * @param node Nodul de pe care se creeaza zona din matrice
 * @param startX Pozitia initiala de pe axa Ox de unde se creeaza zona din matrice
 * @param startY Pozitia initiala de pe axa Oy de unde se creeaza zona din matrice
 * @param width Latimea zonei
 * @param height Inaltimea zonei
 */
void make_pixel_matrix_from_tree(RGB*** matrix, Quadtree *node, int startX, int startY, int width, int height);

#endif