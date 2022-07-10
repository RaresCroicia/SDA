//
// Created by florin on 4/14/22.
//

#ifndef SD_LABS_TRIE_H
#define SD_LABS_TRIE_H

#define NUM_CHILDREN 26

#define CHAR_TO_IDX(ch)     (int) (ch - 'a')           /**< Converteste un caracter la indexul din vectorul de copii */
#define IDX_TO_CHAR(idx)    (char) ((char) idx + 'a')  /**< Converteste un index din vectorul de copii la caracterul corespunzator */

#define TRUE 1
#define FALSE 0

/**
 * @brief Structura unui nod dintr-o trie ce stocheaza
 *        literele mici din alfabet.
 *
 * Nu mai este necesar campul de date deoarece indexul
 * la care se afla copilul indica ce litera din alfabet
 * este asignata acelui nod. De exemplu, litera 'a'
 * se va afla mereu la indexul 0.
 *
 */
typedef struct trieNode {
    int isWordTerminal;           /**< Boolean care indica daca nodul curent este sfarsitul unui cuvant */
    struct trieNode **children;   /**< Copiii stocati alfabetic */
    struct trieNode *parent;      /**< Parintele nodului curent */
} trieNode_t;

/**
 * Initializeaza un nou nod in trie
 *
 * @return
 *      Noul nod
 */
trieNode_t *trieInitNode();

/**
 * Elibereaza memoria ocupata de un nod
 * @param node
 */
void trieFreeNode(trieNode_t *node);

/**
 * Elibereaza memoria ocupata de trie
 *
 * @param root
 */
void trieDestroy(trieNode_t **root);

/**
 * Verifica daca nodul curent este frunza
 *
 * @param node
 *      Nodul
 * @return
 *      - 1 (true) daca este frunza
 *      - 0 (false) altfel
 */
int trieNodeIsLeaf(trieNode_t *node);

/**
 * Afiseaza caracterele copiilor nodului dat
 *
 * @param node
 */
void printNodeCharacters(trieNode_t *node);

/**
 * Insereaza un cuvant in arborele de prefixuri
 *
 * @param root
 *      Radacina arborelui (poate fi modificata)
 * @param word
 *      Cuvantul ce va fi inserat
 */
void trieInsertWord(trieNode_t **root, char *word);

/**
 * Verifica daca arborele contine cuvantul cautat
 *
 * @param root
 *      Radacina arborelui
 * @param word
 *      Cuvantul cautat
 *
 * @return
 *      - 1 (true) daca s-a gasit cuvantul
 *      - 0 (false) altfel
 */
int trieContainsWord(trieNode_t *root, char *word);

/**
 * Sterge un cuvant din arbore
 *
 * @param root
 *      Radacina arborelui
 * @param word
 *      Cuvantul care va fi sters
 */
void trieDeleteWord(trieNode_t **root, char *word);

/**
 * Afiseaza toate cuvintele care incep cu prefixul dat
 *
 * @param root
 * @param prefix
 */
void triePrefixMatching(trieNode_t *root, char *prefix);

#endif //SD_LABS_TRIE_H
