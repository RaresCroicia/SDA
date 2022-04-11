#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

QNode_t *initQueueNode(BTNode *data) {
    QNode_t *newNode = malloc(sizeof(QNode_t));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;

    return newNode;
}

queue_t *initQueue() {
    queue_t *newQueue = malloc(sizeof(queue_t));
    newQueue->head = newQueue->tail = NULL;
    newQueue->len = 0;

    return newQueue;
}

void enqueue(queue_t *queue, BTNode *data) {
    if (data == NULL) {
        return;
    }

    QNode_t *new = initQueueNode(data);

    if (queue->len == 0) {
        // Coada goala
        queue->head = new;
        queue->tail = new;
    } else {
        // Introducere la inceput de coada
        new->next = queue->head;
        queue->head->prev = new;
        queue->head = new;
    }
    ++queue->len;
}

BTNode *dequeue(queue_t *queue) {
    BTNode *ret;

    if (queue->len == 0) {
        // Coada este goala
        return NULL;
    }
    // Elimina nod de la final
    QNode_t *aux = queue->tail;

    if (queue->len == 1) {
        // Coada are un singur element
        queue->tail = NULL;
        queue->head = NULL;
    } else {
        // Coada are mai multe elemente
        queue->tail = aux->prev;
        queue->tail->next = NULL;
    }
    --queue->len;

    // Copiez valoarea nodului
    ret = aux->data;

    // Setez statusul pe 0

    free(aux);
    return ret;
}

BTNode *peek(queue_t *queue) {
    if (queue->len == 0) {
        return NULL;
    }
    return queue->tail->data;
}
