/**
 * @author Florin Dumitrescu
 *
 * Definirea structurilor unei liste si functii de initializare si afisare ale acestora
 */

#ifndef SD_LABS_LIST_H
#define SD_LABS_LIST_H

#define STATUS_OK   0   
#define STATUS_ERR  1

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct list {
    node_t *head;
    node_t *tail;
    int len;
} list_t;

node_t *initNode(int value);

list_t *initList();

void destroyList(list_t *list);

void print_list(list_t *list);

#endif //SD_LABS_LIST_H
