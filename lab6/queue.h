/**
 *  @author Florin Dumitrescu
 *
 *  Header pentru queue.c
 *
 *  O coada poate fi reprezentata printr-o lista dublu
 *  inlantuita pentru o complexitate de timp cat mai mica
 */

#ifndef SD_LABS_QUEUE_H
#define SD_LABS_QUEUE_H

#include <stddef.h>

#include "binary_tree.h"

typedef struct QNode {
    BTNode *data;
    struct QNode *next;
    struct QNode *prev;
} QNode_t;

typedef struct queue {
    QNode_t *head;
    QNode_t *tail;
    size_t len;
} queue_t;

QNode_t *initQueueNode(BTNode *data);

queue_t *initQueue();

/**
 * Adauga un nou nod la inceputul listei cu valoarea data.
 *
 * Complexitate temporala: O(1)
 *
 * @param queue coada
 * @param value valoarea noului nod
 */
void enqueue(queue_t *queue, BTNode *data);

/**
 * Elimina ultimul nod din coada
 *
 * Complexitate temporala: O(1)
 *
 * @param queue coada
 * @param status
 *          - STATUS_OK (0) daca operatia s-a efectuat cu succes
 *          - STATUS_ERR (1) altfel
 *
 * @return valoarea nodului eliminat
 */
BTNode *dequeue(queue_t *queue);

/**
 * Returneaza valoarea ultimului nod din coada fara a-l elimina
 *
 * Complexitate temporala: O(1)
 *
 * @param queue coada
 * @param status
 *          - STATUS_OK (0) daca operatia s-a efectuat cu succes
 *          - STATUS_ERR (1) altfel
 *
 * @return valoarea ultimului nod
 */
BTNode *peek(queue_t *queue);

#endif //SD_LABS_QUEUE_H
