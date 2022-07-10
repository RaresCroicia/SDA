//
// Created by florin on 4/28/22.
//

#ifndef SD_LABS_PRIORITY_QUEUE_H
#define SD_LABS_PRIORITY_QUEUE_H

#include "stddef.h"
#include "heap.h"

/**
 * Un element in coada de prioritati
 */
typedef struct pQueueItem {
    void *data;             /**< campul de date */
    size_t dataSize;       /**< memoria ocupata de campul de date */
    int priority;          /**< prioritatea elementului */
} pQueueItem_t;

/**
 * @brief Initializeaza un element din coada de prioritati
 *
 * @param value Valoarea campului de date
 * @param dataSize Memoria ocupata de campul de date
 * @param priority Prioritate elementului
 *
 * @return Noul element
 */
pQueueItem_t *initPQueueItem(void *value, size_t dataSize, int priority);

/**
 * @brief Insereaza un element in coada de prioritati
 *
 * @param pQueue Coada in care se va face inserarea
 * @param value Valoarea elementului inserat
 * @param dataSize Memoria ocupata de un element in memorie
 * @param priority Prioritatea elementului
 */
void priorityEnqueue(heapArray_t **pQueue, void *value, size_t dataSize, int priority);

/**
 * @brief Extrage elementul cu cea mai mare prioritate din coada
 *
 * @param pQueue Coada din care se va extrage elementul
 * @param ret Elementul returnat
 *
 * @return
 *      - STATUS_OK:                Elementul a fost extras cu succes
 *      - ERR_INDEX_OUT_OF_BOUNDS:  Nu se poate accesa elementul din coada de la indexul dat
 *      - ERR_EMPTY_HEAP:           Coada este goala
 */
heap_err_t priorityDequeue(heapArray_t **pQueue, pQueueItem_t *ret);

/**
 * @brief Returneaza elementul cu prioritatea cea mai mare
 *
 * @param pQueue Coada de prioritati
 * @param ret Elementul cu cea mai mare/mica prioritate
 *
 * @return
 *      - STATUS_OK:                Elementul exista
 *      - ERR_EMPTY_HEAP:           Coada este goala
 */
heap_err_t priorityPeek(heapArray_t *pQueue, void *ret);

/**
 * @brief Sterge elementul din movila de la pozitia idx si ii returneaza valoarea
 *
 * @param pQueue Movila din care se va sterge radacina
 * @param idx Indexul elementului ce va fi sters
 * @param ret Valoarea din varful movilei
 *
 * @return
 *      - STATUS_OK:                Elementul a fost extras cu succes
 *      - ERR_INDEX_OUT_OF_BOUNDS:  Nu se poate accesa elementul din coada de la indexul dat
 *      - ERR_EMPTY_HEAP:           Coada este goala
 */
heap_err_t extractNode(heapArray_t **pQueue, size_t idx, void *ret);

/**
 * @brief Modifica prioritatea unui nod
 *
 * @param pQueue Movila
 * @param idx Indexul elementului ce va fi modificat
 * @param newPriority Noua prioritate a nodului
 *
 * @return
 *      - STATUS_OK:                Elementul a fost extras cu succes
 *      - ERR_INDEX_OUT_OF_BOUNDS:  Nu se poate accesa elementul din coada de la indexul dat
 *      - ERR_EMPTY_HEAP:           Coada este goala
 */
heap_err_t changeNodePriority(heapArray_t **pQueue, size_t idx, int newPriority);

#endif //SD_LABS_PRIORITY_QUEUE_H
