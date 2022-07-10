#include <stdio.h>
#include <stdlib.h>

#include "lab03.h"

#define DEBUG 1

#define RED_TEXT()      \
    printf("\033[0;31m");

#define GREEN_TEXT()    \
    printf("\033[0;32m");

#define RESET_TEXT()    \
    printf("\033[0m");

#define BOLD_TEXT()     \
    printf("\033[1m");

#define LAB3_ASSERT(list, test, msg)        \
    if (test) {                             \
        GREEN_TEXT()                        \
        printf("PASSED: %s\n", msg);        \
    } else {                                \
        RED_TEXT()                          \
        printf("FAILED: %s\n", msg);        \
    }                                       \
    RESET_TEXT()


static int check_list(sl_list_t *list, const int * const v, size_t v_size)
{
    node_t *aux = list->head;

    if (DEBUG) {
        print_list_int(list);

        printf("%-20s", "Lista dorita: ");

        for (int i = 0; i < v_size - 1; i++) {
            printf("%d->", v[i]);
        }
        printf("%d\n", v[v_size - 1]);
    }

    for (int i = 0; i < v_size; i++) {
        if (aux == NULL) {
            RED_TEXT()
            printf("Lista e mai scurta decat vectorul\n");
            RESET_TEXT()
            return -1;
        }

        if (*aux->data != v[i]) {
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

static void insert_element_in_array(int *v, int value, int position, size_t *v_size)
{
    int aux;

    for (int i = *v_size - 1; i >= position; i--) {
        aux = v[i + 1];
        v[i + 1] = v[i];
    }
    v[position] = value;
    ++(*v_size);
}

static void remove_element_from_array(int *v, uint position, size_t *v_size)
{
    for (uint i = position; i < *v_size - 1; i++) {
        v[i] = v[i + 1];
    }
    --(*v_size);
}

void test_insert(sl_list_t *list, int *v, size_t *v_size)
{
    BOLD_TEXT()
    printf("Adaugare elemente in lista\n");
    RESET_TEXT()

    int ret;

    // Inserare la inceput de lista
    ret = insert_node(list, 2, 0);
    insert_element_in_array(v, 2, 0, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la inceputul listei (value = 2)")

    ret = insert_node(list, 1, 0);
    insert_element_in_array(v, 1, 0, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la inceputul listei (value = 1)")

    ret = insert_node(list, 0, 0);
    insert_element_in_array(v, 0, 0, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la inceputul listei (value = 0)")

    // Inserare la sfarsit de lista
    ret = insert_node(list, 6, list->len - 1);
    insert_element_in_array(v, 6, *v_size, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la sfarsitul listei (value = 6)")

    ret = insert_node(list, 7, list->len - 1);
    insert_element_in_array(v, 7, *v_size, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la sfarsitul listei (value = 7)")

    ret = insert_node(list, 8, list->len - 1);
    insert_element_in_array(v, 8, *v_size, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la sfarsitul listei (value = 8)")

    // Inserare intr-o pozitie aleatoare
    ret = insert_node(list, 3, 3);
    insert_element_in_array(v, 3, 3, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la pozitia 3 (value = 3)")

    ret = insert_node(list, 4, 4);
    insert_element_in_array(v, 4, 4, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la pozitia 4 (value = 4)")

    ret = insert_node(list, 5, 5);
    insert_element_in_array(v, 5, 5, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0, "Inserare la pozitia 5 (value = 5)")

    // Inserare intr-o pozitie inexistenta
    ret = insert_node(list, -1, -1);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == -1,
                "Eroare la inserare intr-o pozitie din afara intervalului (position = -1)")

    ret = insert_node(list, -1, list->len);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == -1,
                "Eroare la inserare intr-o pozitie din afara intervalului (position = 9)")
}

void test_remove_by_value(sl_list_t *list, int *v, size_t *v_size)
{
    BOLD_TEXT()
    printf("Eliminare elemente cu o anumita valoare\n");
    RESET_TEXT()

    int ret;

    ret = remove_node_by_key(list, 0);
    remove_element_from_array(v, 0, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0,
                "Eliminare nod cu o valoare existenta, aflat la inceputul listei (value = 0)")

    ret = remove_node_by_key(list, 4);
    remove_element_from_array(v, 3, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0,
                "Eliminare nod cu o valoare existenta, aflat in mijlocul listei (value = 4)")

    ret = remove_node_by_key(list, 8);
    remove_element_from_array(v, 6, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0,
                "Eliminare nod cu o valoare existenta, aflat la sfarsitul listei (value = 8)")

    ret = remove_node_by_key(list, 10);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == -1,
                "Eroare la eliminare nod cu o valoare inexistenta (value = 10)")
}

void test_remove_by_position(sl_list_t *list, int *v, size_t *v_size)
{
    BOLD_TEXT()
    printf("Eliminare elemente de la o anumita pozitie\n");
    RESET_TEXT()

    int ret;

    ret = remove_node_at_position(list, 0);
    remove_element_from_array(v, 0, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0,
                "Eliminare nod de la inceputul listei (position = 0, value = 1)")

    ret = remove_node_at_position(list, 3);
    remove_element_from_array(v, 3, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0,
                "Eliminare nod din mijlocul listei (position = 3, value = 6)")

    ret = remove_node_at_position(list, list->len - 1);
    remove_element_from_array(v, *v_size - 1, v_size);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == 0,
                "Eliminare nod de la sfarsitul listei (position = 3, value = 7)")

    ret = remove_node_at_position(list, list->len + 1);
    LAB3_ASSERT(list, check_list(list, v, *v_size) == 0 && ret == -1,
                "Eliminare nod de la sfarsitul listei (position = 4, value = NAN)")
}

void test_ex2()
{
    BOLD_TEXT()
    printf("Cautarea elementelor de pe pozitii din afara intervalului\n");
    RESET_TEXT()

    sl_list_t *list = init_list();

    for (int i = 9; i >= 0; i--) {
        insert_node(list, i, 0);
    }

    print_list_int(list);

    LAB3_ASSERT(list, cyclic_search(list, 5) == 5, "Elementul de pe pozitia 5 este 5")
    LAB3_ASSERT(list, cyclic_search(list, -1) == 9, "Elementul de pe pozitia -1 este 9")
    LAB3_ASSERT(list, cyclic_search(list, 10) == 0, "Elementul de pe pozitia 10 este 0")
    LAB3_ASSERT(list, cyclic_search(list, -5) == 5, "Elementul de pe pozitia -5 este 5")

    destroy_list(list);
}


// int main(void)
// {
//     /* Initializare lista */
//     sl_list_t *list = init_list();

//     /* Valorile dorite in lista dupa inserare */
//     size_t v_size = 0;
//     int *v = malloc(100 * sizeof(int));

//     test_insert(list, v, &v_size);
//     printf("\n\n");

//     test_remove_by_value(list, v, &v_size);
//     printf("\n\n");

//     test_remove_by_position(list, v, &v_size);
//     printf("\n\n");

//     BOLD_TEXT()
//     printf("Testare lungime lista\n");
//     RESET_TEXT()

//     if (list->len == v_size) {
//         GREEN_TEXT()
//         printf("Lungimea listei este corecta: %lu\n", list->len);
//     } else {
//         RED_TEXT()
//         printf("Lungimea listei nu este corecta. Valoare asteptata: %lu; valoare returnata: %lu\n",
//                v_size,
//                list->len);
//     }
//     RESET_TEXT()

//     // Eliberare memorie
//     destroy_list(list);
//     free(v);
//     printf("\n\n");

//     // Exercitiul 2
//     test_ex2();

//     return 0;
// }

int main(){
    sl_list_t *list;
    list = init_list();
    int ans = insert_node(list, 12, 0);
    ans = insert_node(list, 13, 1);
    node_t *aux = list->head;
    while(aux->next != NULL){
        printf("%d\n", *aux->data);
        aux = aux->next;
    }
}