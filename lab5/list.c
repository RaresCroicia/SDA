//
// Created by florin on 3/30/22.
//

#include <stdlib.h>
#include <stdio.h>

#include "list.h"

node_t *initNode(int value) {
    node_t *node = malloc(sizeof(node_t));

    node->data = value;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

list_t *initList() {
    list_t *q = malloc(sizeof(list_t));

    q->head = NULL;
    q->tail = NULL;
    q->len = 0;

    return q;
}

void destroyList(list_t *list) {
    node_t *aux;

    while (list->len > 0) {
        // Se sterg toate elementele din lista
        aux = list->head;
        list->head = aux->next;
        free(aux);
        --list->len;
    }
    free(list);
}

void print_list(list_t *list) {
    node_t *aux = list->head;

    printf("%-25s", "Lista contine:");

    if (aux == NULL) {
        // Lista vida
        printf("NULL\n");
        return;
    }

    while (aux->next != NULL) {
        printf("%d -> ", aux->data);
        aux = aux->next;
    }
    printf("%d\n", aux->data);
}
