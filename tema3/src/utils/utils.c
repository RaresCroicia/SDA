#include "utils.h"
#include <stdlib.h>

Queue* init_queue(){
    Queue *q = calloc(1, sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
    return q;
}

queue_node* init_queue_node(int nod, int mask, double sum){
    queue_node* rez = calloc(1, sizeof(queue_node));
    rez->info = calloc(1, sizeof(nod_djikstra));
    rez->info->nod = nod;
    rez->info->mask = mask;
    rez->info->sum = sum;
    rez->next = NULL;
    return rez;
}

void enqueue(Queue** q, int nod, int mask, double sum){
    queue_node *this = init_queue_node(nod, mask, sum);
    if((*q)->len == 0){
        (*q)->head = (*q)->tail = this;
        ++(*q)->len;
        return;
    }
    (*q)->tail->next = this;
    (*q)->tail = this;
    ++(*q)->len;
    
}

nod_djikstra* dequeue(Queue** q){
    queue_node *cap = (*q)->head;
    (*q)->head = (*q)->head->next;
    nod_djikstra* rez = cap->info;
    cap->next = NULL;
    free(cap);
    --(*q)->len;
    if((*q)->len == 1)
        (*q)->tail = (*q)->head;
    if((*q)->len == 0)
        (*q)->tail = NULL;
    return rez;
}

double min_double(double a, double b){
    return a < b ? a : b;
}

bool is_from_zone(int *zone, int n, int who){
    for(int i = 0; i < n; i++)
        if(zone[i] == who) 
            return TRUE;
    return FALSE;
}

bool is_empty(Queue *q){
    return q->len == 0;
}

list init_list(){
    list lista;
    lista.head = NULL;
    lista.len = 0;
    return lista;
}

void add_to_list(list* lista, int nod, int mask, double sum){
    nod_djikstra *this = calloc(1, sizeof(nod_djikstra));
    list_node *rez = calloc(1, sizeof(list_node));
    this->nod = nod;
    this->mask = mask;
    this->sum = sum;
    rez->info = this;
    rez->next = NULL;
    list_node *aux = lista->head;
    if(aux == NULL){
        lista->head = rez;
        lista->len ++;
    }
    else{
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = rez;
        lista->len ++;
    }
}

bool is_visited(list lista, int nod, int mask){
    list_node *aux = lista.head;
    while(aux != NULL){
        if(aux->info->nod == nod && aux->info->mask == mask)
            return TRUE;
        aux = aux->next;
    }
    return FALSE;
}

int get_index_zone(int *zone, int n, int who){
    for(int i = 0; i < n; i++)
        if(zone[i] == who)
            return i;
    return -1;
}


void free_queue(Queue **Q){
    queue_node *cap = (*Q)->head;
    while(cap != NULL){
        queue_node *aux = cap;
        cap = cap->next;
        free(aux->info);
        free(aux);
    }
    free(*Q);
}