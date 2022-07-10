#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t hash_func(const char *key, int cap){
    size_t index = 0;
    for(int i = 0; i < strlen(key); i++){
        index += (key[i] % 26 + GAUSS(i))%cap;
    }
    index %= cap;
    return index;
}

HMap* init_map(size_t (*func)(const char*, int)){
    HMap *this = calloc(1, sizeof(HMap));
    this->elements = 0;
    this->capacity = 10;
    this->hashFunc = func;
    this->table = calloc(this->capacity, sizeof(HMNode*));
    return this;
}

HMNode* init_node(const char* key, int value){
    HMNode* this = calloc(1, sizeof(HMNode));
    this->key = key;
    this->value = value;
    return this;
}

double get_load(HMap* map){
    return (double)map->elements / (double)map->capacity;
}

void extend_capacity(HMap* map){
    map->capacity *= 2;
}

size_t offset(size_t x){
    return x;
}

void insert_map(HMap *hmap, const char *key, int value) {
    size_t keyHash = hmap->hashFunc(key, hmap->capacity);
    size_t index = keyHash;
    HMNode *element = init_node(key, value);
    size_t x = 1;
    if (get_load(hmap) > LOAD_THRESHOLD) {
        extend_capacity(hmap);
    }
    while (!is_bucket_available(hmap->table[index])) {
        if(hmap->table[index] != NULL){
            if(!strcmp(hmap->table[index]->key, key)){
                fprintf(stdout, "Key \"%s\" already used! Replacing old value (%d) with new value (%d)\n", key, hmap->table[index]->value, value);
                hmap->table[index] = element;
                return;
            }
        }
        index = (keyHash + offset(x)) % hmap->capacity;
        x += 1;
        
    }
    hmap->elements ++;
    hmap->table[index] = element;
}

HMNode* get_removed(){
    HMNode* this = init_node("thiswasused", 1);
    return this;
}

int is_bucket_available(HMNode* element){
    if(element == NULL)
        return TRUE;
    if(element == get_removed())
        return TRUE;
    return FALSE;
}

int get_value(HMap *hmap, const char *key){
    size_t keyHash = hmap->hashFunc(key, hmap->capacity);
    size_t index = keyHash;
    size_t x = 1;
    while (hmap->table[index] != NULL && index < hmap->capacity) {
        if(!strcmp(hmap->table[index]->key, key))
            break;
        index = (keyHash + offset(x)) % hmap->capacity;
        x += 1;
    }
    if(index >= hmap->capacity){
        printf("Value not found!\n");
        return -1;
    }
    if(hmap->table[index] == NULL){
        printf("Value not found!\n");
        return -1;
    }
    return hmap->table[index]->value;
}

void remove_map(HMap *hmap, const char *key) {
    size_t keyHash = hmap->hashFunc(key, hmap->capacity);
    size_t index = keyHash;
    size_t x = 1;
    while (hmap->table[index] != NULL) {
        if (!strcmp(hmap->table[index]->key, key)) {
            hmap->table[index] = get_removed();
            hmap->elements --;
            return;
        }
        index = (keyHash + offset(x)) % hmap->capacity;
        x += 1;
        if (x >= hmap->capacity) {
            fprintf(stdout, "Element with key \"%s\" doesn't exist!\n", key);
            return;
        }
    }
}

int contains_key(HMap *hmap, const char *key){
    size_t keyHash = hmap->hashFunc(key, hmap->capacity);
    size_t index = keyHash;
    size_t x = 1;
    while (hmap->table[index] != NULL && index < hmap->capacity) {
        if(!strcmp(hmap->table[index]->key, key))
            break;
        index = (keyHash + offset(x)) % hmap->capacity;
        x += 1;
    }
    if(index >= hmap->capacity)
        return FALSE;

    if(hmap->table[index] == NULL)
        return FALSE;
    return TRUE;
}