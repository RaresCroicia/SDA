#include "liste.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int check_command(char* choice){
    char* choice_cut = choice+2;
    if(!strcmp(choice_cut, "e1"))
        return e1;
    if(!strcmp(choice_cut, "e2"))
        return e2;
    if(!strcmp(choice_cut, "e3"))
        return e3;
    if(!strcmp(choice_cut, "u"))
        return u;
    if(!strcmp(choice_cut, "c"))
        return c;
    if(strstr(choice_cut, "st"))
        return st;

    printf("Choice not found!\n");
    return ERROR;
}

real window_average(TNod* middle){
    //Se cunoaste ca sunt 5 elemente in fereastra
    real first = middle->prev->prev->value;
    real second = middle->prev->value;
    real third = middle->value;
    real fourth = middle->next->value;
    real fifth = middle->next->next->value;

    real sum = first + second + third + fourth + fifth;
    sum /= 5; 

    return sum;
}

real standard_deviation(TNod* middle){
    real first = middle->prev->prev->value;
    real second = middle->prev->value;
    real third = middle->value;
    real fourth = middle->next->value;
    real fifth = middle->next->next->value;
    
    real average = window_average(middle);

    first = pow(first-average, 2);
    second = pow(second-average, 2);
    third = pow(third-average, 2);
    fourth = pow(fourth-average, 2);
    fifth = pow(fifth-average, 2);

    real sum = first + second + third + fourth + fifth;
    sum /= 5;
    sum = sqrt(sum);

    return sum;
}

int is_in_bounds(real value, real lower_bound, real upper_bound){
    if(lower_bound > upper_bound)
        return FALSE;
    if(value <= upper_bound && value >= lower_bound)
        return TRUE;
    return FALSE; 
}

int is_in_bounds_uint(uint value, uint lower_bound, uint upper_bound){
    if(lower_bound > upper_bound)
        return FALSE;
    if(value <= upper_bound && value >= lower_bound)
        return TRUE;
    return FALSE; 
}

TPair median(TNod* middle){
    TPair answer;
    answer.timestamp = middle->timestamp; //Tinem minte timestamp-ul elementului central
    TNod* first = middle->prev->prev;
    TNod* second = middle->prev;
    TNod* fourth = middle->next;
    TNod* fifth = middle->next->next;
    //ordered este o lista in care elementele ferestrei sunt ordonate
    TList* ordered = init_list();
    ordered = priority_insert_value(ordered, first->timestamp, first->value);
    ordered = priority_insert_value(ordered, second->timestamp, second->value);
    ordered = priority_insert_value(ordered, middle->timestamp, middle->value);
    ordered = priority_insert_value(ordered, fourth->timestamp, fourth->value);
    ordered = priority_insert_value(ordered, fifth->timestamp, fifth->value);
    TNod* medianNode = ordered->head->next->next; //aflam mediana ferestrei sortate
    answer.value = medianNode->value;
    destroy_list(ordered);
    return answer;

}

int extract_number(char* string){
    char* number = string+4;
    int digits = strlen(number);
    int pow = 1;
    for(int i = 0; i < digits-1; i++)
        pow *= 10;
    int answer = 0;
    for(int i = 0; i < digits; i++){
        answer += (number[i]-'0') * pow;
        pow /= 10;
    }
    return answer;
}

TList* get_left_list(TNod* middle){
    TList* new_list = init_list();
    TNod* first = middle->prev->prev->prev;
    TNod* second = middle->prev->prev;
    TNod* third = middle->prev;
    new_list = add_to_list(new_list, new_list->length, first->timestamp, first->value);
    new_list = add_to_list(new_list, new_list->length, second->timestamp, second->value);
    new_list = add_to_list(new_list, new_list->length, third->timestamp, third->value);
    return new_list;
}

TList* get_right_list(TNod* middle){
    TList* new_list = init_list();
    TNod* first = middle->next->next->next;
    TNod* second = middle->next->next;
    TNod* third = middle->next;
    new_list = add_to_list(new_list, new_list->length, first->timestamp, first->value);
    new_list = add_to_list(new_list, new_list->length, second->timestamp, second->value);
    new_list = add_to_list(new_list, new_list->length, third->timestamp, third->value);
    return new_list;
}

real scaling_factor(uint timestamp, TList* left, TList* right){
    real up = timestamp - left->tail->timestamp;
    real down = right->tail->timestamp - left->tail->timestamp;
    return up/down;
}

real w(uint i, uint k){
    real up = ((real)i / (k-1)) * ((real)i / (k-1)) * 0.9 + 0.1;
    real down = 0;
    for(real j = 0; j < k; j++)
        down += (j / (k-1)) * (j / (k-1)) * 0.9 + 0.1;
    
    return up/down;
}

real value_calculation(TList* left, TList* right, uint timestamp, real C, uint k){
    real sum_left = 0;
    real sum_right = 0;

    TNod* left_iter = left->head;
    TNod* right_iter = right->head;

    for(int i = 0; i < k; i++, left_iter = left_iter->next)
        sum_left += left_iter->value * w(i,k);
    for(int i = 0; i < k; i++, right_iter = right_iter->next)
        sum_right += right_iter->value * w(i,k);
    

    return (1-C) * sum_left + C * sum_right;

}
