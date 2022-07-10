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

node_t *init_node(const int *value)
{
    node_t *nod = NULL;
    nod = malloc(sizeof(node_t));
    nod->data = value;
    nod->next = malloc(sizeof(nod->next));
    nod->next = NULL;
    return nod;
}


void free_node(node_t *node)
{
    free(node->data);
    free(node->next);
    free(node);
}

sl_list_t *init_list()
{
    sl_list_t *lista = NULL;
    lista = malloc(sizeof(sl_list_t));
    lista->head = malloc(sizeof(node_t));
    lista->tail = malloc(sizeof(node_t));
    lista->len = 0;
    return lista;
}

void destroy_list(sl_list_t *list)
{
    node_t *act = list->head;
    if(act == NULL)
        return;

    do{
        act = act->next;
        free_node(list->head);
        list->head = act;
    }while(list->head != list->tail);

    free(list);
}

int insert_node(sl_list_t *list, int value, uint position)
{
    if(position == 0){
        node_t *nod = NULL;
        nod = init_node(value);
        nod->next = list->head;
        list->head = nod;
        return 0;

    }
    int i = 0;
    
    node_t *parc = list->head;
    while(i != position - 1){
        if(parc == NULL)
            return -1;
        i++;
        parc = parc->next;
    }
    node_t *aux = NULL;
    aux = malloc(sizeof(node_t));
    aux->data = value;
    aux->next = parc->next;
    parc->next = aux;

    return 0;
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