#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "liste.h"
#include "utils.h"
#include "work.h"

int main(int argc, char** argv){
    //Cazul in care nu sunt introduse deloc argumente
    if(argc < 2){
        printf("Give me arguments! See the documentation to see the commands!\n");
        return 0;
    }

    //Citim elementele din lista
    TList* list = init_list();
    uint number_elements;
    fscanf(stdin, "%u", &number_elements);
    for(uint index = 0; index < number_elements; ++index){
        uint timestamp;
        real value;
        fscanf(stdin, "%u%lf", &timestamp, &value);
        list = add_to_list(list, list->length, timestamp, value);
    }
    //Prelucram lista in functie de argumente
    for(int i = 1; i < argc; i++){
        int choice = check_command(argv[i]);
        if(choice == e1)
            list = remove_exceptions_statistically(list);
        else if(choice == e2)
            list = median_filtered(list);
        else if(choice == e3)
            list = average_filtered(list);
        else if(choice == u)
            list = frequency_uniform(list);
        else if(choice == c)
            list = data_completion(list);
        else if(choice == st){
            print_statistics(list, extract_number(argv[i]));
            destroy_list(list);
            return 0;
        }
    }
    //Afisam lista si o distrugem
    print_list(list);
    destroy_list(list);
    
    //Terminam programul
    return 0;
}
