#include <stdio.h>
#include <stdlib.h>

#include "lab05.h"
#include "stack.h"
#include "queue.h"

#define DEBUG 1

#define RED_TEXT()      \
    printf("\033[0;31m");

#define GREEN_TEXT()    \
    printf("\033[0;32m");

#define CYAN_TEXT()    \
    printf("\033[0;36m");

#define RESET_TEXT()    \
    printf("\033[0m");

#define HEADER_TEXT()     \
    printf("\033[1;33m");

#define SD_ASSERT(test, msg)        \
    if (test) {                             \
        GREEN_TEXT()                        \
        printf("PASSED: %s\n", msg);        \
    } else {                                \
        RED_TEXT()                          \
        printf("FAILED: %s\n", msg);        \
    }                                       \
    RESET_TEXT()                             \
    printf("\n");

int *string_to_vect(char* s, int n) {
    int *v = calloc(n, sizeof(float));
    char *p = s;

    for (int i = 0; i < n; i++) {
        v[i] = (int) strtol(p, &p, 10);
    }

    return v;
}

void print_vect(int *v, int n) {
    printf("%-25s", "Lista dorita: ");

    if (n == 0) {
        printf("NULL\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        printf("%d -> ", v[i]);
    }
    printf("%d\n", v[n - 1]);
}

static void print_vect_ex4(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

static int compare_vects(int *a, int *b, int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return -1;
    }
    return 0;
}

static int check_result(list_t *list, int *v, int n)
{
    node_t *aux = list->head;

    if (DEBUG) {
        print_list(list);
        print_vect(v, n);
    }

    for (int i = 0; i < n; i++) {
        if (aux == NULL) {
            RED_TEXT()
            printf("Lista e mai scurta decat vectorul\n");
            RESET_TEXT()
            return -1;
        }

        if (aux->data != v[i]) {
            RED_TEXT()
            printf("Lista nu are toate valorile egale cu cele ale vectorului\n");
            RESET_TEXT()
            return -1;
        }

        aux = aux->next;
    }

    if (aux != NULL) {
        RED_TEXT()
        printf("Lista e mai lunga decat vectorul\n");
        RESET_TEXT()
        return -1;
    }
    return 0;
}

void test_queue() {
    HEADER_TEXT()
    printf("Teste operatii pe coada\n\n");
    RESET_TEXT()

    queue_t *queue = initList();
    int ret, status;
    int *v;
    int n = 0;
    char *msg = malloc(100);

    /* Test enqueue */
    enqueue(queue, 7);
    v = string_to_vect("7", ++n);
    SD_ASSERT(check_result(queue, v, n) == 0, "Test enqueue (value = 7)")
    free(v);

    enqueue(queue, 3);
    v = string_to_vect("3 7", ++n);
    SD_ASSERT(check_result(queue, v, n) == 0, "Test enqueue (value = 3)")
    free(v);

    enqueue(queue, 10);
    v = string_to_vect("10 3 7", ++n);
    SD_ASSERT(check_result(queue, v, n) == 0, "Test enqueue (value = 10)")

    /* Test peek */
    ret = peek(queue, &status);
    sprintf(msg, "Test peek. Expected 7, got %d; status = %d", ret, status);
    SD_ASSERT(check_result(queue, v, n) == 0 && ret == 7 && status == STATUS_OK, msg)
    free(v);

    /* Test dequeue */
    ret = dequeue(queue, &status);
    sprintf(msg, "Test dequeue. Expected 7, got %d; status = %d", ret, status);
    v = string_to_vect("10 3", --n);
    SD_ASSERT(check_result(queue, v, n) == 0 && ret == 7 && status == STATUS_OK, msg)
    free(v);

    ret = dequeue(queue, &status);
    sprintf(msg, "Test dequeue. Expected 3, got %d; status = %d", ret, status);
    v = string_to_vect("10", --n);
    SD_ASSERT(check_result(queue, v, n) == 0 && ret == 3 && status == STATUS_OK, msg)
    free(v);

    ret = dequeue(queue, &status);
    sprintf(msg, "Test dequeue. Expected 10, got %d; status = %d", ret, status);
    v = string_to_vect("", --n);
    SD_ASSERT(check_result(queue, v, n) == 0 && ret == 10 && status == STATUS_OK, msg)

    dequeue(queue, &status);
    sprintf(msg, "Test dequeue empty queue. status = %d", status);
    SD_ASSERT(check_result(queue, v, n) == 0 && status == STATUS_ERR, msg)

    /* Test peek empty queue */
    peek(queue, &status);
    sprintf(msg, "Test peek empty queue. status = %d", status);
    SD_ASSERT(check_result(queue, v, n) == 0 && status == STATUS_ERR, msg)
    free(v);

    destroyList(queue);
    free(msg);
}

void test_stack() {
    HEADER_TEXT()
    printf("Teste operatii pe stiva\n\n");
    RESET_TEXT()

    stack_t *stack = initList();
    int ret, status;
    int *v;
    int n = 0;
    char *msg = malloc(100);

    /* Test push */
    push(stack, 7);
    v = string_to_vect("7", ++n);
    SD_ASSERT(check_result(stack, v, n) == 0, "Test push (value = 7)")
    free(v);

    /* Test push */
    push(stack, 3);
    v = string_to_vect("3 7", ++n);
    SD_ASSERT(check_result(stack, v, n) == 0, "Test push (value = 3)")
    free(v);

    /* Test push */
    push(stack, 10);
    v = string_to_vect("10 3 7", ++n);
    SD_ASSERT(check_result(stack, v, n) == 0, "Test push (value = 10)")

    /* Test top */
    ret = top(stack, &status);
    sprintf(msg, "Test top. Expected 10, got %d; status = %d", ret, status);
    SD_ASSERT(check_result(stack, v, n) == 0 && ret == 10 && status == STATUS_OK, msg)
    free(v);

    /* Test pop */
    ret = pop(stack, &status);
    sprintf(msg, "Test pop. Expected 10, got %d; status = %d", ret, status);
    v = string_to_vect("3 7", --n);
    SD_ASSERT(check_result(stack, v, n) == 0 && ret == 10 && status == STATUS_OK, msg)
    free(v);

    ret = pop(stack, &status);
    sprintf(msg, "Test pop. Expected 3, got %d; status = %d", ret, status);
    v = string_to_vect("7", --n);
    SD_ASSERT(check_result(stack, v, n) == 0 && ret == 3 && status == STATUS_OK, msg)
    free(v);

    ret = pop(stack, &status);
    sprintf(msg, "Test pop. Expected 7, got %d; status = %d", ret, status);
    v = string_to_vect("", --n);
    SD_ASSERT(check_result(stack, v, n) == 0 && ret == 7 && status == STATUS_OK, msg)

    pop(stack, &status);
    sprintf(msg, "Test pop empty stack. status = %d", status);
    SD_ASSERT(check_result(stack, v, n) == 0 && status == STATUS_ERR, msg)

    /* Test top empty stack */
    top(stack, &status);
    sprintf(msg, "Test top empty stack. status = %d", status);
    SD_ASSERT(check_result(stack, v, n) == 0 && status == STATUS_ERR, msg)
    free(v);

    destroyList(stack);
    free(msg);
}

void test_ex3() {
    HEADER_TEXT()
    printf("Teste paranteze echilibrate folosind stiva\n\n");
    RESET_TEXT()

    SD_ASSERT(checkBalancedBrackets("[([])]") == 1, "Test paranteze balansate '[([])]'")
    SD_ASSERT(checkBalancedBrackets("[({[]})(([]))]") == 1, "Test paranteze balansate '[({[]})(([]))]'")
    SD_ASSERT(checkBalancedBrackets("({[}])") == 0, "Test paranteze nebalansate '({[}])'")
    SD_ASSERT(checkBalancedBrackets("([{}][])(") == 0, "Test paranteze nebalansate '([{}][])('")
}

void test_ex4() {
    HEADER_TEXT()
    printf("Teste Radix Sort folosind cozi\n\n");
    RESET_TEXT()

    int *v, *w;
    int n = 6;

    /* Test vector cu toate numerele < 10 */
    v = string_to_vect("5 3 6 8 3 1", n);
    w = string_to_vect("1 3 3 5 6 8", n);

    radixSort(v, n);

    if (DEBUG) {
        printf("%-25s", "Vectorul sortat: ");
        print_vect_ex4(v, n);

        printf("%-25s", "Vectorul asteptat: ");
        print_vect_ex4(w, n);
    }
    SD_ASSERT(compare_vects(v, w, n) == 0, "Test sortare vectorul [5 3 6 8 3 1]")
    free(v);
    free(w);

    /* Test vector cu intregi cu numar egal de digiti */
    v = string_to_vect("532 354 812 612 332 119", n);
    w = string_to_vect("119 332 354 532 612 812", n);

    radixSort(v, n);

    if (DEBUG) {
        printf("%-25s", "Vectorul sortat: ");
        print_vect_ex4(v, n);

        printf("%-25s", "Vectorul asteptat: ");
        print_vect_ex4(w, n);
    }
    SD_ASSERT(compare_vects(v, w, n) == 0, "Test sortare vectorul [532 354 812 612 332 119]")
    free(v);
    free(w);

    /* Test vector cu intregi cu numar diferit de digiti */
    v = string_to_vect("12 34 65 8 213 111", n);
    w = string_to_vect("8 12 34 65 111 213", n);

    radixSort(v, n);

    if (DEBUG) {
        printf("%-25s", "Vectorul sortat: ");
        print_vect_ex4(v, n);

        printf("%-25s", "Vectorul asteptat: ");
        print_vect_ex4(w, n);
    }
    SD_ASSERT(compare_vects(v, w, n) == 0, "Test sortare vectorul [12 34 65 8 213 111]")
    free(v);
    free(w);
}

int main() {
    test_queue();
    test_stack();
    test_ex3();
    test_ex4();

    return 0;
}