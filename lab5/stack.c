#include <stdlib.h>
#include "stack.h"

void push(stack_t *stack, int value) {
    if(stack->head == NULL){
        node_t *nod = initNode(value);
        stack->head = nod;
        stack->len = 1;
        return;
    }
    node_t *nod = initNode(value);
    nod->next = stack->head;
    stack->head = nod;
    stack->len ++;
    return;
}

int pop(stack_t *stack, int *status) {
    if(stack->head == NULL || stack->len == 0){
        *status = STATUS_ERR;
        //printf("Stiva e deja goala!\n");
        return -1;
    }
    node_t *aux = stack->head;
    stack->head = stack->head->next;
    int value = aux->data;
    free(aux);
    stack->len--;
    *status = STATUS_OK;
    return value;
}

int top(stack_t *stack, int *status) {
    if(stack->len == 0 || stack->head == NULL){
        *status = STATUS_ERR;
        return -1;
    }
    *status = STATUS_OK;
    return stack->head->data;
}
