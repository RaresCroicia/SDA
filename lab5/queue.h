/**
 *  @author Florin Dumitrescu
 *
 *  Header pentru queue.c
 *
 *  O coada poate fi reprezentata printr-o lista dublu inlantuita
 */

#ifndef SD_LABS_QUEUE_H
#define SD_LABS_QUEUE_H

#include "list.h"

typedef list_t queue_t;

/**
 * Adauga un nou nod la inceputul listei cu valoarea data.
 *
 * Complexitate temporala: O(1)
 *
 * @param queue coada
 * @param value valoarea noului nod
 */
void enqueue(queue_t *queue, int value);

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
int dequeue(queue_t *queue, int *status);

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
int peek(queue_t *queue, int *status);

#endif //SD_LABS_QUEUE_H
