#ifndef __TREE__
#define __TREE__
#include <inttypes.h>
#include "rgb.h"

/**
 * @brief Structura cu informatiile unui nod din arbore
 * 
 */
typedef struct QuadtreeNode{
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) QuadtreeNode;

/**
 * @brief Structura de arbore
 * 
 */
typedef struct Quadtree{
    QuadtreeNode *info;
    int index;
    struct Quadtree *first;
    struct Quadtree *second;
    struct Quadtree *third;
    struct Quadtree *fourth;
} Quadtree;

/**
 * @brief Structura unui element din coada
 * 
 */
typedef struct QueueNode{
    struct QueueNode *next;
    Quadtree *elem;
}QueueNode;


/**
 * @brief Structura de coada
 * 
 */
typedef struct Queue{
    QueueNode *head, *tail;
    int len;
}Queue;

/**
 * @brief Functie care aloca un nod cu valorile initiale date
 * 
 * @param index Pozitia pe care o va avea nodul in vector
 * @param red Componenta rosie a culorii zonei pe care o descrie nodul
 * @param green Componenta verde a culorii zonei pe care o descrie nodul
 * @param blue Componenta albastra a culorii zonei pe care o descrie nodul
 * @param area Aria zonei pe care o descrie nodul
 * @param top_left Pozitia pe care o va avea copilul din NW in vector
 * @param top_right Pozitia pe care o va avea copilul din NE in vector
 * @param bottom_right Pozitia pe care o va avea copilul din SE in vector
 * @param bottom_left Pozitia pe care o va avea copilul din SW in vector
 * @return Nodul din arbore 
 */
Quadtree* quadtree_alloc(int index, unsigned char red, unsigned char green, unsigned char blue,
                        uint32_t area, int32_t top_left, 
                        int32_t top_right, int32_t bottom_right, int32_t bottom_left);

/**
 * @brief Functia care creeaza arborele in mod recursiv
 * 
 * @param node Nodul care se va crea in arbore
 * @param matrix Matricea de pixeli
 * @param startX Pozitia initiala de pe axa Ox a zonei reprezentata de nodul actual din arbore
 * @param startY Pozitia initiala de pe axa Oy a zonei reprezentata de nodul actual din arbore
 * @param width Latimea zonei reprezentata de nodul actual
 * @param height Inaltimea zonei reprezentata de nodul actual
 * @param factor Toleranta de eroare
 * @return Nodul din arbore
 */
Quadtree* create_quadtree(Quadtree* node, RGB** matrix, int startX, int startY, int width, int height, int factor);

/**
 * @brief Functie care returneaza numarul de noduri din arbore
 * 
 * @param node Nodul de la care se calculeaza numarul de noduri
 * @return Numarul de noduri
 */
int count_nodes(Quadtree* node);

/**
 * @brief Verifica daca un nod este frunza
 * 
 * @param node Nodul respectiv
 * @return 1 sau 0 - Este sau nu este frunza
 */
int isLeaf(Quadtree* node);

/**
 * @brief Functie care returneaza numarul de frunze
 * 
 * @param node Nodul de la care se calculeaza numarul de frunze
 * @return Numarul de frunze
 */
int count_leaves(Quadtree* node);

/**
 * @brief Functie care seteaza indexul fiecarui nod
 *        folosind abordarea BFS-ului
 * 
 * @param root Nodul de unde incepe indexarea
 * @return Arborele indexat
 */
Quadtree* index_tree(Quadtree* root);

/**
 * @brief Functie care seteaza pentru fiecare nod ce indexi au copiii
 *        folosind abordarea BFS-ului
 * 
 * @param root Nodul de unde incepe setarea
 * @return Arborele dupa modificari
 */
Quadtree* index_tree_children(Quadtree* root);

/**
 * @brief Creeaza vectorul de "noduri" pe baza arborelui cuaternar
 *        folosind abordarea BFS-ului
 * 
 * @param root Nodul de la care se incepe introducerea in vector
 * @return Vectorul
 */
QuadtreeNode* make_vector(Quadtree* root);

/**
 * @brief Functie pentru afisarea elementelor din vector (folosita la debugging)
 *        
 * @param vector Vectorul
 * @param length Lungimea acestuia
 */
void print_vector(QuadtreeNode* vector, int length);

/**
 * @brief Elibereaza memoria ocupata de arbore
 * 
 * @param node 
 */
void destroy_tree(Quadtree** node);

/**
 * @brief Functie care creeaza arborele cuaternar in mod recursiv in functie de vectorul de noduri
 * 
 * @param vector Vectorul de noduri
 * @param index indexul nodului
 * @return Nodul cu index-ul respectiv
 */
Quadtree* create_quadtree_from_vector(QuadtreeNode* vector, int index);

/**
 * @brief Functia care initializeaza o coada
 * 
 * @return Coada
 */
Queue* init_queue();

/**
 * @brief Functie care initializeaza un nod de coada
 * 
 * @param elem Nodul din arbore care va fi adaugat in coada
 * @return Nodul din coada
 */
QueueNode* queue_node_init(Quadtree* elem);

/**
 * @brief Functia care adauga element in coada
 * 
 * @param queue Coada
 * @param elem Elementul
 */
void enqueue(Queue** queue, Quadtree* elem);

/**
 * @brief Functia care scoate un element din coata
 * 
 * @param queue Coada
 * @return Elementul scos
 */
Quadtree* dequeue(Queue** queue);

/**
 * @brief Verifica daca o coada este goala
 * 
 * @param queue Coada
 * @return 1 sau 0 - Coada e goala sau nu
 */
int empty(Queue* queue);

/**
 * @brief Functia de afisare a unui arbore (folosita la debugging)
 * 
 * @param root Nodul de unde se incepe afisarea
 */
void print_arbore(Quadtree* root);

/**
 * @brief Functia care interschimba doua noduri
 * 
 * @param a Nodul 1
 * @param b Nodul 2
 */
void swap_node(Quadtree** a, Quadtree** b);

/**
 * @brief Roteste orizontal arborele
 * 
 * @param node Nodul de la care se incepe rotirea
 */
void horizontal_rotation(Quadtree** node);

/**
 * @brief Roteste vertical arborele
 * 
 * @param node Nodul de la care se incepe rotirea
 */
void vertical_rotation(Quadtree** node);

#endif