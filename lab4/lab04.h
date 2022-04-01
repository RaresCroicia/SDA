#ifndef SD_LABS_LAB04_H
#define SD_LABS_LAB04_H

#define RED_TEXT()      \
    printf("\033[0;31m");

#define GREEN_TEXT()    \
    printf("\033[0;32m");

#define CYAN_TEXT()    \
    printf("\033[0;36m");

#define RESET_TEXT()    \
    printf("\033[0m");

#define HEADER_TEXT()     \
    printf("\033[1;33m");

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct dl_list {
    node_t *head;
    node_t *tail;
    int len;
} list_t;

/**
 * Initializeaza un nod din lista
 *
 * @param value: Valoarea ce va fi stocata in campul data al nodului nou creat
 */
node_t * init_node(int value);

/**
 * Initializeaza o lista vida
 *
 * @return Noua lista
 */
list_t *init_list();

/**
 * Elibereaza memoria ocupata de un nod
 *
 * @param nod
 */
void free_node(node_t *nod);

/**
 * Elibereaza zona de memorie ocupata de o lista. Daca lista nu e vida,
 * se vor sterge toate nodurile din lista inainte de a elibera
 * memoria ocupata de structura listei
 *
 * @param list
 */
void destroy_list(list_t *list);

/**
 * Afiseaza lista primita ca parametru
 *
 * @param list
 */
void print_list(list_t *list);

/**
 * Afiseaza in ordine inversa lista primita ca parametru
 *
 * @param list
 */
void print_list_reversed(list_t *list);

/**
 * Insereaza un nou element in lista
 *
 * @param list Lista in care se va face inserarea
 * @param value Valoarea stocata in noul nod
 * @param position Pozitia la care va fi inserat nodul
 * @return
 *      -  0: Inserarea a avut loc cu succes
 *      - -1: Au aparut probleme la inserare
 */
int insert_node(list_t *list, int value, int position);

/**
 * Sterge un nod din lista
 *
 * @param list Lista din care se va sterge
 * @param position Pozitia nodului care va fi sters
 * @return
 *      -  0: Stergerea a avut loc cu succes
 *      - -1: Au aparut probleme la stergere
 */
int remove_node(list_t *list, int position);

/**
 * Insereaza un nou nod in lista in asa fel incat lista sa ramana sortata descrescator
 *
 * @param list Lista in care se va face inserarea
 * @param value Valoarea stocata in noul nod
 * @return
 *      -  0: Inserarea a avut loc cu succes
 *      - -1: Au aparut probleme la inserare
 */
int insert_sorted_desc(list_t *list, int value);

/**
 * Elimina valorile duplicate dintr-o lista primita ca parametru.
 * Nu se efectueaza modificari asupra listei primite
 *
 * @param list
 * @return
 *          Lista fara valori duplicate, sortata descrescator
 */
list_t *remove_duplicates(list_t *list);

#endif //SD_LABS_LAB04_H
