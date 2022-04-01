//
// Created by florin on 3/22/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "lab04.h"

node_t * init_node(int value) {
    node_t *new_node = malloc(sizeof(node_t));

    new_node->data = value;

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

list_t *init_list() {
    list_t *new_list = malloc(sizeof(list_t));

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;

    return new_list;
}

void free_node(node_t *nod)
{
    //free(nod->data);
    free(nod);
}

void destroy_list(list_t *list) {
    node_t *aux;

    /* Se sterg toate nodurile din lista, incepand de la coada */
    while (list->len > 0) {
        aux = list->tail;                   // Se retine un pointer catre ultimul nod din lista
        list->tail = list->tail->prev;      // Se muta pointerul cozii cu un nod mai in spate
        free_node(aux);                // Se elibereaza memoria ocupata de nodul eliminat
        --list->len;                        // Se decrementeaza lungimea listei
    }

    /* Se elibereaza memoria ocupata de structura listei */
    free(list);
}

void print_list(list_t *list) {
    node_t *aux = list->head;

    printf("%-25s", "Lista construita (->):");

    if (aux == NULL) {
        // Lista vida
        printf("NULL\n");
        return;
    }

    while (aux != list->tail) {
        printf("%d -> ", aux->data);
        aux = aux->next;
    }
    printf("%d\n", aux->data);
}

void print_list_reversed(list_t *list) {
    /* TODO 1.a.
     * Se va porni de la ultimul nod din lista si se va parcurge lista
     * pana cand se va ajunge la primul nod
     */

    node_t *aux = list->tail;

    printf("%-25s", "Lista construita (->):");

    if (aux == NULL) {
        // Lista vida
        printf("NULL\n");
        return;
    }

    while (aux != list->head) {
        printf("%d -> ", aux->data);
        aux = aux->prev;
    }
    printf("%d\n", aux->data);
}

int insert_node(list_t *list, int value, int position) {
    /* TODO 1.b.
     * Se vor trata urmatoarele cazuri:
     *  - Pozitia nu este in intervalul [0, len] => return -1
     *  - Inserarea se face intr-o lista vida
     *  - Inserarea se face la inceputul listei
     *  - Inserarea se face la sfarsitul listei
     *  - Inserarea se face intr-o pozitie intermediara:
     *      - Pozitia este mai aproape de inceputul listei => parcurgerea se va face de la inceputul listei
     *      - Pozitia este mai aproape de sfarsitul listei => parcurgerea se va face de la sfarsitul listei
     */

    if(position < 0 || position > list->len)
        return -1;

    if(position != 0 && list->head == NULL)
        return -1;

    if(list->head == NULL){
        node_t *nod = init_node(value);
        list->head = nod;
        list->tail = nod;
        list->len ++;
        return 0;
    }

    if(position == 0){
        node_t *nod = init_node(value);
        list->head->prev = nod;
        nod->next = list->head;
        list->head = nod;
        list->len ++;
        return 0;
    }

    if(position == list->len){
        node_t *nod = init_node(value);
        list->tail->next = nod;
        nod->prev = list->tail;
        list->tail = nod;
        list->len ++;
        return 0;
    }

    if(position == 1){
        node_t *nod = init_node(value);
        nod->next = list->head->next;
        nod->prev = list->head;
        list->head->next->prev = nod;
        list->head->next = nod;
        list->len++;
        return 0;
    }

    if(position == list->len - 1){
        node_t *nod = init_node(value);
        nod->next = list->tail;
        nod->prev = list->tail->prev;
        list->tail->prev = nod;
        list->tail->prev->next = nod;
        list->len ++;
        return 0;
    }

    int i;
    node_t *aux = list->head;
    for(i = 0; i < position-1; i++, aux = aux->next);
    node_t *nod = init_node(value);
    nod->next = aux->next;
    nod->prev = aux;
    aux->next->prev = nod;
    aux->next = nod;
    list->len++;

    return 0;
}

int remove_node(list_t *list, int position) {
    /* TODO 1.c.
     * Se vor trata urmatoarele cazuri:
     *  - Pozitia nu este in intervalul [0, len - 1] sau lista este vida (len == 0) => return -1
     *  - Stergerea se face de la inceputul listei
     *  - Stergerea se face de la sfarsitul listei
     *  - Stergerea se face dintr-o pozitie intermediara:
     *      - Pozitia este mai aproape de inceputul listei => parcurgerea se va face de la inceputul listei
     *      - Pozitia este mai aproape de sfarsitul listei => parcurgerea se va face de la sfarsitul listei
     */

    if(position < 0 || position > list->len - 1)
        return -1;

    if(position == 0){
        node_t *aux = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free_node(aux);
        list->len --;
        return 0;
    }

    if(position == list->len - 1){
        node_t *aux = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free_node(aux);
        list->len --;
        return 0;
    }
    int i;
    node_t *aux = list->head;
    for(i = 0; i < position; i++, aux = aux->next);
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    list->len--;    
    free_node(aux);
    return 0;
}

int insert_sorted_desc(list_t *list, int value) {

    if(list->head == NULL){
        node_t *nod = init_node(value);
        list->head = nod;
        list->tail = nod;
        list->len++;
        return 0;
    }

    if(value >= list->head->data){
        node_t *nod = init_node(value);
        nod->next = list->head;
        list->head->prev = nod;
        list->head = nod;
        list->len++;
        return 0;
    }

    if(value <= list->tail->data){
        node_t *nod = init_node(value);
        nod->prev = list->tail;
        list->tail->next = nod;
        list->tail = nod;
        list->len++;
        return 0;
    }

    node_t *aux = list->head;
    while(aux->data > value)
        aux = aux->next;
    
    node_t *curr = init_node(value);
    /// 8 7 6 5 3 --- 4 
    curr->next = aux;
    curr->prev = aux->prev;
    aux->prev->next = curr;
    aux->prev = curr;
    list->len++;

    return 0;
}

list_t *remove_duplicates(list_t *list) {
    /*
     * TODO 3
     * Pornind de la lista primita ca parametru, se construieste
     * o noua lista care va contine doar valori unicat.
     * Lista finala va fi sortata descrescator
     */

    if(list->len == 1)
        return list;
    
    list_t *new_list = init_list();
    node_t *aux = list->head;
    while(aux->next != NULL){
        int ok = insert_sorted_desc(new_list, aux->data);
        aux = aux->next;
    }
    int ok = insert_sorted_desc(new_list, aux->data);
    int i;
    aux = new_list->head;
    for(i = 0; i < new_list->len-1; i++){
        node_t *next = aux->next;
        if(aux->data == next->data){
            remove_node(new_list, i);
            i--;
        }
        aux = next;
    }

    
    return new_list;
}
