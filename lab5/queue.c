#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void enqueue(queue_t *queue, int value) {
    if(queue->head == NULL){
        node_t *nod = initNode(value);
        queue->head = nod;
        queue->tail = nod;
        queue->len = 1;
        return;
    }
    node_t *nod = initNode(value);
    nod->next = queue->head;
    queue->head->prev = nod;
    queue->head = nod;
    queue->len++;
    printf("LEN = %d\n", queue->len);
    return;
}

int dequeue(queue_t *queue, int *status) {
    if(queue->len == 0){
        *status = STATUS_ERR;
        return -1;
    }
    if(queue->len == 1){
        *status = STATUS_OK;
        int value = queue->tail->data;
        queue->head = NULL;
        queue->tail = NULL;
        queue->len--;
        return value;
    }
    node_t *aux = queue->tail;
    int val = aux->data;
    //queue->tail->prev->next = NULL;
    queue->tail = queue->tail->prev;
    queue->tail->next = NULL;
    queue->len --;
    printf("LEN = %d\n", queue->len);
    free(aux);
    *status = STATUS_OK;
    return val;
}

int peek(queue_t *queue, int *status) {
    if(queue->head == NULL || queue->len == 0){
        *status = STATUS_ERR;
        return -1;
    }
    *status = STATUS_OK;
    return queue->tail->data;
}
