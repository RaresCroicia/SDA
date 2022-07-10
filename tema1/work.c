#include "liste.h"
#include "utils.h"
#include "work.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

TList* remove_exceptions_statistically(TList* list){
    TList* new_list = init_list();
    TNod* iter = list->head->next->next;
    TNod* upper_bound = list->tail->prev;

    //Adaugam cele 2 noduri initiale, deoarece stim sigur ca nu o sa fie sterse
    new_list = add_to_list(new_list, new_list->length, list->head->timestamp, list->head->value);
    new_list = add_to_list(new_list, new_list->length, list->head->next->timestamp, list->head->next->value);

    //Parcurgem fiecare nod si verificam apartenenta la interval
    while(iter != upper_bound){
        real average = window_average(iter);
        real deviation = standard_deviation(iter);
        if(is_in_bounds(iter->value, average-deviation, average+deviation))
            new_list = add_to_list(new_list, new_list->length, iter->timestamp, iter->value);
        iter = iter->next;
    }

    //Adaugam si ultimele doua noduri, deoarece stim sigur ca nu o sa fie sterse
    new_list = add_to_list(new_list, new_list->length, upper_bound->timestamp, upper_bound->value);
    new_list = add_to_list(new_list, new_list->length, upper_bound->next->timestamp, upper_bound->next->value);
    destroy_list(list);
    return new_list;
}

TList* median_filtered(TList* list){
    TList* new_list = init_list();
    TNod* iter = list->head->next->next;
    TNod* upper_bound = list->tail->prev;
    while(iter != upper_bound){
        TPair rez = median(iter); //aflam mediana fiecarei ferestre si creem lista de mediane
        new_list = add_to_list(new_list, new_list->length, rez.timestamp, rez.value);
        iter = iter->next;
    }
    destroy_list(list);
    return new_list;
}

TList* average_filtered(TList* list){
    TList* new_list = init_list();
    TNod* iter = list->head->next->next;
    TNod* upper_bound = list->tail->prev;
    while(iter != upper_bound){
        TPair rez;
        rez.value = window_average(iter); 
        rez.timestamp = iter->timestamp;
        new_list = add_to_list(new_list, new_list->length, rez.timestamp, rez.value);
        iter = iter->next;
    }
    destroy_list(list);
    return new_list;
}

TList* frequency_uniform(TList* list){
    TNod* iter = list->head->next;
    while(iter != NULL){
        if(is_in_bounds_uint(iter->timestamp - iter->prev->timestamp, 100, 1000)){ //verificam proprietatea
            iter->value = (iter->value + iter->prev->value) / 2; 
            iter->timestamp = (iter->timestamp + iter->prev->timestamp) / 2;
        }
        iter = iter->next;
    }
    return list;
}

void print_statistics(TList* list, int frequency){
    TList* ordered = init_list();
    TNod* iter = list->head;
    while(iter != NULL){
        ordered = priority_insert_value(ordered, iter->timestamp, iter->value);
        iter = iter->next;
    }
    real lower_bound = floor(ordered->head->value);
    real upper_bound = lower_bound + frequency;
    iter = ordered->head;
    uint contor = 0;
    while(iter != NULL){
        if(iter->value > upper_bound){
            if(contor > 0)
            printf("[%0.0lf, %0.0lf] %u\n", lower_bound, upper_bound, contor);
            while(!is_in_bounds(iter->value, lower_bound, upper_bound)){
                lower_bound = upper_bound;
                upper_bound = lower_bound + frequency;
            }
            contor = 1;
        }
        else
            contor ++;
        iter = iter->next;
    }
    if(contor > 0)
    printf("[%0.0lf, %0.0lf] %u\n", lower_bound, upper_bound, contor);
    destroy_list(ordered);
}

TList* data_completion(TList* list){
    TNod* iter = list->head;
    int i = 0;
    uint k = 3;
    while(iter->next != NULL){
        uint upper_bound = iter->next->timestamp;
        uint lower_bound = iter->timestamp;
        uint aux_timestamp = lower_bound + 200;
        if(upper_bound - lower_bound > 1000){
            TList *left_list, *right_list;
            left_list = get_left_list(iter->next);
            right_list = get_right_list(iter);
            while(aux_timestamp < upper_bound){
                real C = scaling_factor(aux_timestamp, left_list, right_list);
                real final_value = value_calculation(left_list, right_list, aux_timestamp, C, k);
                list = priority_insert_timestamp(list, aux_timestamp, final_value);
                aux_timestamp += 200;
            }
            destroy_list(left_list);
            destroy_list(right_list);
        }
        iter = iter->next;
    }
    return list;
}
