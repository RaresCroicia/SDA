//
// Created by florin on 4/4/22.
//

#ifndef SD_LABS_BINARY_TREE_H
#define SD_LABS_BINARY_TREE_H

#include "stddef.h"

typedef struct BTNode {
    int data;
    struct BTNode *parent;
    struct BTNode *left;
    struct BTNode *right;
} BTNode;

/**
 * Initializeaza un nod din arbore
 *
 * @param value
 *          valoarea ce va fi stocata in nod
 * @return
 *          referinta catre noul nod
 */
BTNode *initNode(int value);

/**
 * Sterge din memorie arborele
 *
 * @param root
 *          referinta catre noul nod
 */
void destroyTree(BTNode **root);

/**
 * Verifica daca nodul selectat este o frunza in arbore
 *
 * @param node
 *          referinta catre un nod
 * @return
 *      - 0: Nu este frunza
 *      - 1: Este frunza
 */
int isLeaf(BTNode *node);

/**
 * Calculeaza numarul de grade (numarul de copii) ale unui nod
 *
 * @param node
 *          Nodul
 * @return
 *          Numarul de grade ale nodului (0, 1 sau 2)
 */
int getNodeDegrees(BTNode *node);

/**
 * Insereaza un nou nod in arbore, respectand proprietatea arborilor binari ca:
 *      - valoarea copilului din stanga este mai mica decat valoarea nodului curent (node->left->data < node->data)
 *      - valoarea copilului din dreapta este mai mare decat valoarea nodului curent (node->right->data > node->data)
 *
 * Daca valoarea ce se doreste a fi introdusa este egala cu valoarea nodului curent (duplicate), se va face inserarea
 * in partea dreapta.
 *
 * @param root
 *          referinta catre radacina arborelui
 * @param value
 *          valoarea noului nod
 *
 * @return
 *          Noul nod inserat
 */
BTNode *insertNode(BTNode *root, int value);

/**
 * Cauta primul nod din arbore cu valoarea data ca parametru
 *
 * @param root
 *          referinta catre radacina arborelui
 * @param value
 *          valoarea nodului cautat
 * @return
 *      - referinta catre nodul cu valoarea cautata
 *      - NULL daca nu exista un astfel de nod
 */
BTNode *searchNode(BTNode *root, int value);

/**
 * Elimina nodul primit ca parametru din arbore
 *
 * @param root
 *          referinta catre radacina arborelui
 * @param node
 *          referinta catre nodul care va fi eliminat
 */
int removeNode(BTNode **root, BTNode *node);

/**
 * Parcurge arborele in preordine (radacina-stanga-dreapta) si ii afiseaza valorile nodurilor.
 *
 * @param root
 *          referinta catre radacina arborelui
 */
void printPreOrder(BTNode *root);

/**
 * Parcurge arborele in ordine (stanga-radacina-dreapta) si ii afiseaza valorile nodurilor
 *
 * @param root
 *          referinta catre radacina arborelui
 */
void printInOrder(BTNode *root);

/**
 * Parcurge arborele in postordine (stanga-dreapta-radacina) si ii afiseaza valorile nodurilor
 * @param root
 *          referinta catre radacina arborelui
 */
void printPostOrder(BTNode *root);

/**
 * Afla inaltimea arborelui
 *
 * @param root
 *          referinta catre radacina arborelui
 * @return
 *          inaltimea arborelui
 */
int getHeight(BTNode *root);

/**
 * Verifica daca arborele binar este echilibrat
 *
 * @param root
 *          Referinta catre radacina nodului
 * @return
 *          - 0 (Nu e balansat)
 *          - 1 (E balansat)
 */
int isBSTreeBalanced(BTNode *root);

#endif //SD_LABS_BINARY_TREE_H
