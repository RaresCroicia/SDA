#include <stdlib.h>
#include "stack.h"


SNode_t *initStackNode(BTNode *value) {
    SNode_t *newNode = malloc(sizeof(SNode_t));
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

stack_t *initStack() {
    stack_t *newStack = malloc(sizeof(stack_t));
    newStack->top = NULL;
    newStack->len = 0;

    return newStack;
}

void push(stack_t *stack, BTNode *data) {
    if (data == NULL) {
        return;
    }

    SNode_t *new_node = initStackNode(data);

    new_node->next = stack->top;
    stack->top = new_node;
    ++stack->len;
}

BTNode *pop(stack_t *stack) {
    SNode_t *aux = stack->top;
    BTNode *ret;

    if (stack->len == 0) {
        // Stiva e goala
        return NULL;
    }

    // Salvez valoarea nodului
    ret = aux->data;

    // Elimin nodul din stiva
    stack->top = aux->next;
    --stack->len;

    free(aux);

    return ret;
}

BTNode *top(stack_t *stack) {
    if (stack->len == 0) {
        return NULL;
    }
    return stack->top->data;
}
