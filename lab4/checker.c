#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab04.h"

#define DEBUG 1

#define LAB4_ASSERT(test, msg)        \
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

static int check_list(list_t *list, int *v, int n)
{
    node_t *aux = list->head;

    if (DEBUG) {
        print_list(list);
        print_vect(v, n);

        CYAN_TEXT()
        print_list_reversed(list);
        RESET_TEXT()
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

void test_insert(list_t *list, int *n) {
    HEADER_TEXT()
    printf("Adaugare elemente in lista\n\n");
    RESET_TEXT()

    int *v;
    int ret;

    ret = insert_node(list, 5, 0);
    v = string_to_vect("5", ++(*n));
    LAB4_ASSERT(check_list(list, v, (*n)) == 0 && ret == 0, "Inserare in lista vida (pos = 0, value = 5)")
    free(v);

    ret = insert_node(list, 4, 0);
    v = string_to_vect("4 5", ++(*n));
    LAB4_ASSERT(check_list(list, v, (*n)) == 0 && ret == 0, "Inserare la inceputul listei (pos = 0, value = 4)")
    free(v);

    ret = insert_node(list, 8, list->len);
    v = string_to_vect("4 5 8", ++(*n));
    LAB4_ASSERT(check_list(list, v, (*n)) == 0 && ret == 0, "Inserare la sfarsitul listei (pos = 2, value = 8)")
    free(v);

    ret = insert_node(list, 9, list->len);
    v = string_to_vect("4 5 8 9", ++(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Inserare la sfarsitul listei (pos = 3, value = 9)")
    free(v);

    ret = insert_node(list, 3, 1);
    v = string_to_vect("4 3 5 8 9", ++(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Inserare la mijlocul listei (mai aproape de head) "
                                                         "(pos = 1, value = 3)")
    free(v);

    ret = insert_node(list, 6, 3);
    v = string_to_vect("4 3 5 6 8 9", ++(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Inserare la mijlocul listei (mai aproape de tail) "
                                                         "(pos = 3, value = 6)")
    free(v);

    ret = insert_node(list, 7, 4);
    v = string_to_vect("4 3 5 6 7 8 9", ++(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Inserare la mijlocul listei (mai aproape de tail) "
                                                          "(pos = 4, value = 7)")
    free(v);

    ret = insert_node(list, -1, 10);
    v = string_to_vect("4 3 5 6 7 8 9", *n);
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == -1, "Inserare la un index mai mare decat lis->len"
                                                         "(pos = 10, value = -1)")
    free(v);
}

void test_remove(list_t *list, int *n) {
    HEADER_TEXT()
    printf("Eliminare elemente din lista\n\n");
    RESET_TEXT()

    int *v;
    int ret;

    ret = remove_node(list, 0);
    v = string_to_vect("3 5 6 7 8 9", --(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Eliminare de la inceputul listei (pos = 0, value = 4)")
    free(v);

    ret = remove_node(list, list->len - 1);
    v = string_to_vect("3 5 6 7 8", --(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Eliminare de la sfarsitul listei (pos = len - 1, value = 4)")
    free(v);

    ret = remove_node(list, 1);
    v = string_to_vect("3 6 7 8", --(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Eliminare din mijlocul listei (mai aproape de head) "
                                                             "(pos = 1, value = 5)")
    free(v);

    ret = remove_node(list, 2);
    v = string_to_vect("3 6 8", --(*n));
    LAB4_ASSERT(check_list(list, v, *n) == 0 && ret == 0, "Eliminare din mijlocul listei (mai aproape de tail) "
                                                          "(pos = 2, value = 7)")
    free(v);
}

void test_insert_sorted_desc() {
    HEADER_TEXT()
    printf("Inserare elemente intr-o lista sortata descrescator\n\n");
    RESET_TEXT()

    list_t *list = init_list();
    int *v;
    int ret;
    int n = 0;

    ret = insert_sorted_desc(list, 5);
    v = string_to_vect("5", ++n);
    LAB4_ASSERT(check_list(list, v, n) == 0 && ret == 0, "Inserare intr-o lista vida (value = 5)")
    free(v);

    ret = insert_sorted_desc(list, 3);
    v = string_to_vect("5 3", ++n);
    LAB4_ASSERT(check_list(list, v, n) == 0 && ret == 0, "Inserare la sfarsit de lista (value = 3)")
    free(v);

    ret = insert_sorted_desc(list, 9);
    v = string_to_vect("9 5 3", ++n);
    LAB4_ASSERT(check_list(list, v, n) == 0 && ret == 0, "Inserare la inceput de lista (value = 9)")
    free(v);

    ret = insert_sorted_desc(list, 4);
    v = string_to_vect("9 5 4 3", ++n);
    LAB4_ASSERT(check_list(list, v, n) == 0 && ret == 0, "Inserare in mijlocul listei (value = 4)")
    free(v);

    destroy_list(list);
}

void test_duplicates()
{
    HEADER_TEXT()
    printf("Eliminare duplicate dintr-o lista\n\n");
    RESET_TEXT()

    list_t *list = init_list();
    list_t *list_set;
    int *v;

    insert_node(list, 8, 0);
    insert_node(list, 6, 0);
    insert_node(list, 3, 0);
    insert_node(list, 6, 0);
    insert_node(list, 9, 0);
    insert_node(list, 3, 0);
    insert_node(list, 8, 0);
    insert_node(list, 6, 0);

    printf("ORIGINAL\n");
    print_list(list);
    printf("\n");

    printf("SET\n");
    list_set = remove_duplicates(list);
    v = string_to_vect("9 8 6 3", 4);
    LAB4_ASSERT(check_list(list_set, v, 4) == 0, "Eliminare duplicate")

    destroy_list(list);
    destroy_list(list_set);
    free(v);
}


int main()
{
    list_t *list = init_list();
    int n = 0;

    test_insert(list, &n);

    test_remove(list, &n);

    destroy_list(list);

    test_insert_sorted_desc();

    test_duplicates();

    return 0;
}