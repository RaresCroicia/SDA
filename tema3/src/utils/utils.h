#ifndef __utils__
#define __utils__
#define FALSE 0
#define TRUE 1
#define inf 1000000
typedef unsigned char bool;
/**
 * @brief Structura unui nod pentru algoritmul lui djikstra
 * 
 */
typedef struct nodDjikstra{
    int nod;
    int mask;
    double sum;
}nod_djikstra;

/**
 * @brief Structura unui nod din coada
 * 
 */
typedef struct QueueNode{
    struct QueueNode *next;
    nod_djikstra *info;
}queue_node;

/**
 * @brief Structura de coada
 * 
 */
typedef struct Queue{
    int len;
    queue_node *head;
    queue_node *tail;
}Queue;

/**
 * @brief Structura unui nod din lista
 * 
 */
typedef struct listN{
    nod_djikstra *info;
    struct listN *next;
}list_node;

/**
 * @brief Structura de lista
 * 
 */
typedef struct list{
    list_node *head;
    int len;
}list;

/**
 * @brief Functie care initializeaza o coada
 * 
 * @return Coada
 */
Queue* init_queue();

/**
 * @brief Functia de initializare a unui nod din coada
 * 
 * @param nod Nodul la care s-a ajuns - Djikstra
 * @param mask Starea traseului la momentul acela
 * @param sum Drumul pana atunci
 * @return Nodul
 */
queue_node* init_queue_node(int nod, int mask, double sum);

/**
 * @brief Functia de adaugare a unui element in coada
 * 
 * @param q Coada
 * @param nod Nodul la care s-a ajuns - Djikstra
 * @param mask Starea traseului la momentul acela
 * @param sum Drumul pana atunci
 */
void enqueue(Queue** q, int nod, int mask, double sum);

/**
 * @brief Functia de extragere din coada a unui element
 * 
 * @param q Coada
 * @return Informatiile nodului 
 */
nod_djikstra* dequeue(Queue** q);

/**
 * @brief Functia de minim a doua numere reale
 * 
 * @param a 
 * @param b 
 * @return Minimul dintre a si b
 */
double min_double(double a, double b);

/**
 * @brief Functia care verifica daca un nod face parte din zona
 * 
 * @param zone Zona
 * @param n Numarul de case din zona
 * @param who Casa verificata
 * @return Daca exista
 */
bool is_from_zone(int *zone, int n, int who);

/**
 * @brief Functia care vede a cata casa din zona este casa data
 * 
 * @param zone Zona
 * @param n Numarul de case
 * @param who Casa verificata 
 * @return Indexul acesteia
 */
int get_index_zone(int *zone, int n, int who);

/**
 * @brief Functia care verifica daca o coada e goala
 * 
 * @param q Coada
 * @return Valoarea de adevar
 */
bool is_empty(Queue *q);

/**
 * @brief Functia care verifica daca un nod a fost deja vizitat cu starea data
 * 
 * @param lista Lista de verificare
 * @param nod Nodul
 * @param mask Starea
 * @return Valoarea de adevar
 */
bool is_visited(list lista, int nod, int mask);

/**
 * @brief Functia care adauga in lista un element nou
 * 
 * @param lista 
 * @param nod 
 * @param mask 
 * @param sum 
 */
void add_to_list(list* lista, int nod, int mask, double sum);

/**
 * @brief Functia care initializeaza o lista
 * 
 * @return Lista
 */
list init_list();

/**
 * @brief Functia de eliberare a unei cozi
 * 
 * @param Q 
 */
void free_queue(Queue **Q);
#endif