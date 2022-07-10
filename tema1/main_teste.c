#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "liste.h"
#include "utils.h"
#include "work.h"

int main(void){
    TList* list;
    list = init_list();
    // list = add_to_list(list, 0, 100, 0.000000);
    // list = add_to_list(list, 1, 100, 0.314159);
    // list = add_to_list(list, 2, 100, 0.628314);
    // list = add_to_list(list, 3, 300, 0.942464);
    // list = add_to_list(list, 4, 250, -1.743396);
    // list = add_to_list(list, 5, 10, 1.570732);
    // list = add_to_list(list, 6, 100, 1.884844);
    // list = add_to_list(list, 7, 200, 2.198938);
    // list = add_to_list(list, 8, 300, 2.513010);
    // list = add_to_list(list, 9, 250, 2.827057);
    // print_list(list);
    // remove_exceptions_statistically(list);
    // printf("\n");
    // print_list(list);
    // destroy_list(list);

    // printf("\n");

    // list = init_list();
    // list = priority_insert(list, 100, 50);
    // list = priority_insert(list, 100, 30);
    // list = priority_insert(list, 100, 40);
    // list = priority_insert(list, 300, 45);
    // print_list(list);
    // destroy_list(list);

    
    // list = init_list();
         
    // list = add_to_list(list, list->length, 100, 1);
    // list = add_to_list(list, list->length, 100, 2);
    // list = add_to_list(list, list->length, 100, 3);
    // list = add_to_list(list, list->length, 100, 6);
    // list = add_to_list(list, list->length, 100, 19);
    // list = add_to_list(list, list->length, 100, 7);
    // list = add_to_list(list, list->length, 100, 8);
    // list = add_to_list(list, list->length, 100, 6);
    // list = add_to_list(list, list->length, 100, 4);
    // list = add_to_list(list, list->length, 100, 4);
    // list = add_to_list(list, list->length, 100, 4);
    // list = add_to_list(list, list->length, 100, 21);
    // list = add_to_list(list, list->length, 100, 4);
    // list = add_to_list(list, list->length, 100, 2);
    // list = add_to_list(list, list->length, 100, -1);
    // print_list(list);

    int n;
    fscanf(stdin, "%d", &n);
    for(int i = 0; i < n; i++){
        uint ts;
        real vl;
        fscanf(stdin, "%u%lf", &ts, &vl);
        list = add_to_list(list, list->length, ts, vl);
    }
    print_list(list);

}
