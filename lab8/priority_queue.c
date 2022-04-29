//
// Created by florin on 4/25/22.
//

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "priority_queue.h"
#include "heap.h"

/**
 * @brief Functie pentru compararea prioritatilor a 2 elemente
 *
 * @param a Primul element
 * @param b Al doilea element
 * @return
 *      - Un numar negativ daca (a.priority < b.priority)
 *      - 0 (zero) daca (a.priority == b.priority)
 *      - Un numar pozitiv daca (a.priority > b.priority)
 */
int comparePriority(const void *a, const void *b) {
    return ((pQueueItem_t *) a)->priority - ((pQueueItem_t *) b)->priority;
}

pQueueItem_t *initPQueueItem(void *value, size_t dataSize, int priority) {
    pQueueItem_t *newItem = malloc(sizeof(pQueueItem_t));

    newItem->dataSize = dataSize;
    newItem->priority = priority;
    newItem->data = malloc(dataSize);

    /* Copiez valoarea in campul de date */
    memcpy(newItem->data, value, dataSize);

    return newItem;
}

void priorityEnqueue(heapArray_t **pQueue, void *value, size_t dataSize, int priority) {
    pQueueItem_t *item = initPQueueItem(value, dataSize, priority);
    insertHeapNode(pQueue, item, sizeof(pQueueItem_t), comparePriority);
}

heap_err_t priorityDequeue(heapArray_t **pQueue, pQueueItem_t *ret) {
    extractHeapRoot(pQueue, ret, comparePriority);
    return STATUS_OK;
}

heap_err_t priorityPeek(heapArray_t *pQueue, void *ret) {
    if (isHeapEmpty(pQueue)) {
        return ERR_EMPTY_HEAP;
    }

    memcpy(ret, pQueue->data[0], pQueue->dataSize);
    return STATUS_OK;
}

// heap_err_t extractNode(heapArray_t **pQueue, size_t idx, void *ret) {
//     (*pQueue)->data[idx]
//     return STATUS_OK;
// }

heap_err_t changeNodePriority(heapArray_t **pQueue, size_t idx, int newPriority) {
    // TODO
    return STATUS_OK;
}



