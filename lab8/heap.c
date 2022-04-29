#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

int compareInteger(const void *a, const void *b) {
    return (*(int *) a) - (*(int *) b);
}

heapArray_t *initHeap(size_t dataSize) {
    heapArray_t *newHeap = malloc(sizeof(heapArray_t));
    newHeap->size = 0;
    newHeap->capacity = INITIAL_HEAP_CAPACITY;
    newHeap->dataSize = dataSize;

    /* Aloc memorie pentru vector */
    newHeap->data = calloc(INITIAL_HEAP_CAPACITY, sizeof(void *));

    if (newHeap->data == NULL) {
        printf("Eroare la initializare vector\n");
        exit(1);
    }

    for (int i = 0; i < INITIAL_HEAP_CAPACITY; i++) {
        newHeap->data[i] = malloc(dataSize);

        if (newHeap->data[i] == NULL) {
            printf("Eroare la initializare elemente\n");
            exit(1);
        }
    }

    return newHeap;
}

void freeHeap(heapArray_t **heap) {
    /* Eliberez memoria ocupata de fiecare element */
    for (int i = 0; i < (*heap)->capacity; i++) {
        free((*heap)->data[i]);
    }

    /* Eliberez memoria ocupata de vectorul de date si structura */
    free((*heap)->data);
    free(*heap);

    /* Marchez heap-ul ca eliberat */
    *heap = NULL;
}

void increaseCapacity(heapArray_t **heap) {
    (*heap)->capacity *= 2;
    (*heap)->data = realloc((*heap)->data, (*heap)->capacity * sizeof(void *));

    if ((*heap)->data == NULL) {
        printf("Eroare la realocare\n");
        exit(1);
    }

    for (int i = (*heap)->size; i < (*heap)->capacity; i++) {
        (*heap)->data[i] = malloc((*heap)->dataSize);
    }
}

int isHeapEmpty(heapArray_t *heap) {
    return heap->size == 0;
}

heap_err_t swap(heapArray_t *heap, size_t i, size_t j) {
    if (isHeapEmpty(heap))
        return ERR_EMPTY_HEAP;

    if (i >= heap->size || j >= heap->size)
        return ERR_INDEX_OUT_OF_BOUNDS;

    void *tmp = malloc(heap->dataSize);
    memcpy(tmp, heap->data[i], heap->dataSize);
    memcpy(heap->data[i], heap->data[j], heap->dataSize);
    memcpy(heap->data[j], tmp, heap->dataSize);

    free(tmp);

    return STATUS_OK;
}

heap_err_t shiftUp(heapArray_t *heap, size_t idx, int (*compare)(const void *a, const void *b)) {
    if(isHeapEmpty(heap))
        return ERR_EMPTY_HEAP;
    if(idx >= heap->size)
        return ERR_INDEX_OUT_OF_BOUNDS;
    
    int ok = 1;
    while(ok){
        if(idx == 0)
            break;
        if(compare(heap->data[idx], heap->data[PARENT(idx)]) < 0)
            ok = 0;
        else{
            swap(heap, idx, PARENT(idx));
            idx = PARENT(idx);
        }
    }
    return STATUS_OK;
}

heap_err_t shiftDown(heapArray_t *heap, size_t idx, int (*compare)(const void *, const void *)) {
    if(isHeapEmpty(heap))
        return ERR_EMPTY_HEAP;
    if(idx >= heap->size)
        return ERR_INDEX_OUT_OF_BOUNDS;
    
    int ok = 1;
    while(ok){
        size_t idx_swap;
        if(2*idx + 1 >= heap->size || 2*idx + 2 >= heap->size)
            break;
        if(compare(heap->data[2*idx+1], heap->data[2*idx+2]) > 0)
            idx_swap = 2*idx+1;
        else
            idx_swap = 2*idx+2;
        
        if(compare(heap->data[idx], heap->data[idx_swap]) > 0)
            ok = 0;
        else
            swap(heap, idx, idx_swap);
    }
    return STATUS_OK;
}

heap_err_t peekHeap(heapArray_t *heap, void *ret) {
    if (isHeapEmpty(heap)) {
        return ERR_EMPTY_HEAP;
    }

    memcpy(ret, heap->data[0], heap->dataSize);

    return STATUS_OK;
}

void insertHeapNode(heapArray_t **heap, void *value, size_t dataSize, int (*compare)(const void *a, const void *b)) {
    if(*heap == NULL){
        *heap = initHeap(dataSize);
    }
    if((*heap)->capacity == (*heap)->size)
        increaseCapacity(heap);
    
    memcpy((*heap)->data[(*heap)->size++], value, dataSize);
    heap_err_t error = shiftUp(*heap, (*heap)->size-1, compare);
}

heap_err_t extractHeapRoot(heapArray_t **heap, void *ret, int (*compare)(const void *a, const void *b)) {

    if(isHeapEmpty(*heap))
        return ERR_EMPTY_HEAP;
    

    heap_err_t error = peekHeap(*heap, ret);
    swap(*heap, 0, (*heap)->size-1);
    (*heap)->size --;
    shiftDown(*heap, 0, compare);
    return STATUS_OK;
}
