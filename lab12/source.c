#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    HMap* map = init_map(hash_func);
    const char matrix[5][100] = {"buna", "ana", "are", "mere", "buna"};
    for(int i = 0; i < 5; i++){
        if(!contains_key(map, matrix[i]))
            insert_map(map, matrix[i], 1);
        else
            insert_map(map, matrix[i], get_value(map, matrix[i]) + 1);
    }
    remove_map(map, "buna");
    fprintf(stdout, "Sunt %ld cuvinte in dictionar!\n", map->elements);
    for(int i = 0; i < map->capacity; i++)
        if(map->table[i] != NULL)
            if(strcmp(map->table[i]->key, get_removed()->key))
                fprintf(stdout, "%s ==> %d\n", map->table[i]->key, map->table[i]->value);
        
}