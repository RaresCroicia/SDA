#ifndef __hash__
#define __hash__
#include <stdlib.h>
#define GAUSS(i) (i) * (i+1) / 2 
#define TRUE 1
#define FALSE 0
#define LOAD_THRESHOLD 0.75

size_t hash_func(const char* key, int cap);

typedef struct HashMapNode {
    const char *key;
    int value;
}HMNode;

typedef struct HashMap {
    HMNode **table;
    size_t capacity;
    size_t elements;
    size_t (*hashFunc)(const char*, int);
}HMap;

HMNode* get_removed();
int is_bucket_available(HMNode* element);
size_t offset(size_t x);
HMNode* init_node(const char* key, int value);
HMap* init_map(size_t (*func)(const char*, int));
void insert_map(HMap *hmap, const char *key, int value);
int get_value(HMap *hmap, const char *key);
void remove_map(HMap *hmap, const char *key);
int contains_key(HMap *hmap, const char *key);


#endif