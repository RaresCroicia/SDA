#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "priority_queue.h"

int main() {
    /* Testare movila */
    heapArray_t *heap = NULL;
    int ret;

    /* Inserez elemente in movila */
    int v[] = {5, 6, 3, 8, 1, 9};

    for (int i = 0; i < 6; i++) {
        insertHeapNode(&heap, &v[i], sizeof(int), &compareInteger);
    }

    /*
     * Afisare elemente din movila.
     * Primul element trebuie sa fie cel mai mic din vector
     */
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", *(int *) heap->data[i]);
    }
    printf("\n");

    /* Testare functie peek */
    peekHeap(heap, (void *) &ret);

    printf("First element: %d\n", ret);

    /* Eliminare elemente din movila */
    size_t n = heap->size;

    for (int i = 0; i < n; i++) {
        extractHeapRoot(&heap, (void *) &ret, &compareInteger);
        printf("Removed %d\n", ret);
    }

    /* Eliminare element dintr-o movila fara elemente */
    if(extractHeapRoot(&heap, (void *) &ret, &compareInteger) == ERR_EMPTY_HEAP)
        printf("E goala sefu\n");

    /* Eliberez memoria ocupata de movila */
    freeHeap(&heap);


    /* Adaugare elemente in coada de prioritati */
   char value[] = {'a', 'd', 'c', 'h'};
   int priorities[] = {2, 0, 1, 3};

   for (int i = 0; i < 4; i++) {
       priorityEnqueue(&heap, &value[i], sizeof(char), priorities[i]);
   }

   /* Afisare elemente din coada de prioritati */
   for (int i = 0; i < heap->size; i++) {
       printf("%c ", *(char *) ((pQueueItem_t *) heap->data[i])->data);
   }
   printf("\n");

   /* Extragere elemente din coada de prioritati */
   n = heap->size;
   pQueueItem_t pRet;

   for (int i = 0; i < n; i++) {
       priorityDequeue(&heap, (void *) &pRet);

       printf("Removed %c with priority %d\n", *(char *) pRet.data, pRet.priority);
   }

   /* Re-adaugare elemente */
   for (int i = 0; i < 4; i++) {
       priorityEnqueue(&heap, &value[i], sizeof(char), priorities[i]);
   }

//    extractNode(&heap, 2, &pRet);
//    printf("Removed %c\n", (char) pRet.data);
//
//    /* Afisare elemente din coada de prioritati */
//    for (int i = 0; i < heap->size; i++) {
//        printf("%c ", *(char *) ((pQueueItem_t *) heap->data[i])->data);
//    }
//    printf("\n");
//
//    /* Schimbare prioritate */
//    changeNodePriority(&heap, 0, 10);
//
//    /* Afisare elemente din coada de prioritati */
//    for (int i = 0; i < heap->size; i++) {
//        printf("%c ", *(char *) ((pQueueItem_t *) heap->data[i])->data);
//    }
//    printf("\n");

    return 0;
}