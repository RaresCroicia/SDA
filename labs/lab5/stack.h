/**
 *  @author Florin Dumitrescu
 *
 *  Header pentru stack.c
 *  O stiva poate fi reprezentata printr-o lista simplu inlantuita
 */

#ifndef SD_LABS_STACK_H
#define SD_LABS_STACK_H

#include "list.h"

typedef list_t stack_t;

/**
 * Adauga un element in stiva
 *
 * Complexitate temporala: O(1)
 *
 * @param stack stiva
 * @param value valoarea noului nod
 */
void push(stack_t *stack, int value);

/**
 * Elimina nodul din varful stivei
 *
 * Complexitate temporala: O(1)
 *
 * @param stack stiva
 * @param status
 *          - STATUS_OK (0) daca operatia s-a efectuat cu succes
 *          - STATUS_ERR (1) altfel
 *
 * @return
 *      Valoarea nodului eliminat
 */
int pop(stack_t *stack, int *status);

/**
 * Afiseaza valoarea nodului din varful stivei
 *
 * Complexitate temporala: O(1)
 *
 * @param stack stiva
 * @param status
 *          - STATUS_OK (0) daca operatia s-a efectuat cu succes
 *          - STATUS_ERR (1) altfel
 *
 * @return
 *      Valoarea nodului eliminat
 */
int top(stack_t *stack, int *status);

#endif //SD_LABS_STACK_H
