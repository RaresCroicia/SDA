#include <stdio.h>
#include <stdlib.h>

#include "lab03.h"

void print_list_int(sl_list_t *list)
{
    node_t *aux = list->head;

    printf("%-20s", "Lista construita:");

    while (aux->next != NULL) {
        printf("%d->", *aux->data);
        aux = aux->next;
    }
    printf("%d\n", *aux->data);
}

node_t *init_node(int *value)
{
    node_t *nod = NULL;
    nod = malloc(sizeof(*nod));
    nod->data = malloc(sizeof(*nod->data));
    nod->data = value;
    nod->next = NULL;
    return nod;
}

void free_node(node_t *node)
{
    free(node->data);
    free(node);
}

sl_list_t *init_list()
{
    sl_list_t *lista = NULL;
    lista = malloc(sizeof(*lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->len = 0;
    return lista;
}

void destroy_list(sl_list_t *list)
{
    while(list->head != NULL){
        node_t *aux = list->head;
        list->head = list->head->next;
        free_node(aux);
    }
    free(list);
}

int insert_node(sl_list_t *list, int value, uint position)
{
    if(position < 0 && position > list->len){
        return -1;
    }
    if()
}

int remove_node_by_key(sl_list_t *list, int value)
{
    // TODO 1.f
    return 0;
}

int remove_node_at_position(sl_list_t *list, uint position)
{
    // TODO 1.h
    return 0;
}

int cyclic_search(sl_list_t *list, int k)
{
    // TODO 2
    return 0;
}