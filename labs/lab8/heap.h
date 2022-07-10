#ifndef SD_LABS_HEAP_H
#define SD_LABS_HEAP_H

#include <stddef.h>

/**
 * Coduri de eroare
 */
typedef enum {
    STATUS_OK,                      /**< Nicio eroare */
    ERR_EMPTY_HEAP,                 /**< Nu exista elemente in heap */
    ERR_INDEX_OUT_OF_BOUNDS         /**< Indexul se afla in afara intervalului vectorului movilei */
} heap_err_t;

/* Constante */
#define INITIAL_HEAP_CAPACITY   5

/* Macro-uri ajutatoare */
#define PARENT(i)           (((i) - 1) / 2)
#define LEFT_CHILD(i)       (2 * (i) + 1)
#define RIGHT_CHILD(i)      (2 * (i) + 2)

#define MIN(a, b)           ((a) < (b) ? (a) : (b))
#define MAX(a, b)           ((a) > (b) ? (a) : (b))

/**
 * @brief Functia de comparare pentru numere intregi
 *
 * @param a Primul termen al comparatiei
 * @param b Al doilea termen al comparatiei
 *
 * @return
 *      - Un numar negativ daca (a < b)
 *      - 0 (zero) daca (a == b)
 *      - Un numar pozitiv daca (a > b)
 * */
int compareInteger(const void *a, const void *b);

/**
 * @brief Structura unui heap ce foloseste un vector ca structura de date de baza
 */
typedef struct heapArray {
    size_t size;                /**< numarul de elemente din movila */
    size_t capacity;            /**< numarul maxim de elemente ce pot fi stocate in movila */
    void **data;                /**< vectorul in care sunt stocate elementele introduse in movila */
    size_t dataSize;            /**< memoria ocupata de un element */
} heapArray_t;

/**
 * @brief Initializeaza o noua movila (heap)
 *
 * @param dataSize memoria ocupata de un element
 *
 * @return Noua movila (heap)
 */
heapArray_t *initHeap(size_t dataSize);

/**
 *  @brief Elibereaza memoria ocupata de o movila (heap)
 *
 *  @param heap movila ce va fi stearsa
 */
void freeHeap(heapArray_t **heap);

/**
 * @brief Dubleaza capacitatea movilei (heap)
 *
 * @param heap
 */
void increaseCapacity(heapArray_t **heap);

/**
 * Verifica daca movila contine elemente
 *
 * @param heap
 *
 * @return
 *      - 1 (true) daca nu are niciun element
 *      - 0 (false) altfel
 */
int isHeapEmpty(heapArray_t *heap);

/**
 * Interschimba elementele din movila
 *
 * @param heap Movila in care se vor face modificarile
 * @param i Indexul primului element
 * @param j Indexul celuilalt element
 *
 * @return Statusul executiei
 */
heap_err_t swap(heapArray_t *heap, size_t i, size_t j);

/**
 * @brief Interschimba nodul curent cu parintele pana cand o conditie este satisfacuta
 *
 * @param heap Movila in care se vor face modificarile
 * @param idx Indexul nodului ce va fi mutat
 * @param compare Funcitia de comparare a 2 elemente
 *
 * @return Statusul executiei
 */
heap_err_t shiftUp(heapArray_t *heap, size_t idx, int (*compare)(const void *a, const void *b));

/**
 * @brief Interschimba nodul curent cu unul din copii pana cand o conditie este satisfacuta
 *
 * @param heap Movila in care se vor face modificarile
 * @param idx Indexul nodului ce va fi mutat
 * @param compare Functia de comparare a 2 elemente
 *
 * @return Statusul executiei
 */
heap_err_t shiftDown(heapArray_t *heap, size_t idx, int (*compare)(const void *a, const void *b));

/**
 * @brief Returneaza elementul din radacina movilei
 *
 * @param heap Movila din care se citeste
 * @param ret Valoarea din varful movilei
 *
 * @return status executie
 */
heap_err_t peekHeap(heapArray_t *heap, void *ret);

/**
 * @brief Insereaza un element in movila
 *
 * @param heap Movila in care se va face inserarea
 * @param value Valoarea inserata
 * @param dataSize Memoria ocupata de un element
 * @param compare Functie de comparatie a 2 elemente
 */
void insertHeapNode(heapArray_t **heap, void *value, size_t dataSize, int (*compare)(const void *a, const void *b));

/**
 * @brief Sterge elemntul din radacina movilei si ii returneaza valoarea
 *
 * @param heap Movila din care se va sterge radacina
 * @param ret Valoarea din varful movilei
 * @param compare Functie de comparatie a 2 elemente
 *
 * @return status executie
 */
heap_err_t extractHeapRoot(heapArray_t **heap, void *ret, int (*compare)(const void *a, const void *b));

#endif //SD_LABS_HEAP_H
