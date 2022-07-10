#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

TList* init_list(){
    TList* list = NULL;
    list = malloc(sizeof(*list));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

TNod* init_node(uint ts, real val){
    TNod* nod = NULL;
    nod = malloc(sizeof(*nod));
    nod->prev = NULL;
    nod->next = NULL;
    nod->timestamp = ts;
    nod->value = val;
    return nod;
}

void destroy_node(TNod* node){
    node->next = NULL;
    node->prev = NULL;
    free(node);
}

void destroy_list(TList* list){
    if(list == NULL)
        return;
    if(list->head == NULL){
        free(list);
        return;
    }
    TNod* iter = list->head;
    while(iter != NULL){
        TNod* aux = iter;
        iter = iter->next;
        destroy_node(aux);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    free(list);
    //list = NULL;
}

void print_list(TList* list){
    if(list == NULL || list->head == NULL || list->length == 0){
        printf("Lista este vida!\n");
        return;
    }
    TNod* nod = list->head;
    fprintf(stdout, "%u\n", list->length);
    for(;nod != NULL; nod = nod->next)
       fprintf(stdout, "%u %0.2lf\n", nod->timestamp, nod->value);
}

TList* add_to_list(TList* list, uint position, uint ts, real vl){
    if(position < 0 || position > list->length){
        printf("Can't place object {%u, %0.2lf}\n", ts, vl);
        return list;
    }
    TNod* node = init_node(ts, vl);       
    if(position == 0){
        if(list->head == NULL){
            list->head = node;
            list->tail = node;
            list->length = 1;
            return list;
        }
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
        list->length ++;
        return list;
    }

    if(position == list->length){
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        list->length ++;
        return list;
    }

    TNod* aux = list->head;
    for(int i = 0; i < position - 1; i++, aux = aux->next);
    node->next = aux->next;
    node->prev = aux;
    aux->next->prev = node;
    aux->next = node;
    list->length ++;
    return list;
}

TList* remove_from_list(TList* list, uint position){
    if(position < 0 || position > list->length - 1){
        printf("Position out of bounds\n");
        return list;
    }

    if(list->length == 0){
        printf("The list is already empty\n");
        return list;
    }

    if(position == 0){
        TNod* aux = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        destroy_node(aux);
        list->length --;
        return list;
    }

    if(position == list->length - 1){
        TNod* aux = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        destroy_node(aux);
        list->length --;
        return list;
    }

    int i = 0;
    TNod* aux = list->head;
    for(;i < position; i++, aux = aux->next);
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    destroy_node(aux);
    list->length --;
    return list;

}

TList* priority_insert_value(TList* list, uint timestamp, real value){
    TNod* nod = init_node(timestamp, value);
    if(list->head == NULL){
        list->head = nod;
        list->tail = nod;
        list->length = 1;
        return list;
    }
    if(value <= list->head->value){
        nod->next = list->head;
        list->head->prev = nod;
        list->head = nod;
        list->length ++;
        return list;
    }
    if(value >= list->tail->value){
        nod->prev = list->tail;
        list->tail->next = nod;
        list->tail = nod;
        list->length ++;
        return list;
    }

    TNod* aux = list->head;
    for(;value > aux->value; aux = aux->next);
    nod->next = aux;
    nod->prev = aux->prev;
    aux->prev->next = nod;
    aux->prev = nod;
    list->length ++;
    return list;
}

TList* priority_insert_timestamp(TList* list, uint timestamp, real value){
    TNod* nod = init_node(timestamp, value);
    if(list->head == NULL){
        list->head = nod;
        list->tail = nod;
        list->length = 1;
        return list;
    }
    if(timestamp <= list->head->timestamp){
        nod->next = list->head;
        list->head->prev = nod;
        list->head = nod;
        list->length ++;
        return list;
    }
    if(timestamp >= list->tail->timestamp){
        nod->prev = list->tail;
        list->tail->next = nod;
        list->tail = nod;
        list->length ++;
        return list;
    }

    TNod* aux = list->head;
    for(;timestamp > aux->timestamp; aux = aux->next);
    nod->next = aux;
    nod->prev = aux->prev;
    aux->prev->next = nod;
    aux->prev = nod;
    list->length ++;
    return list;
}
