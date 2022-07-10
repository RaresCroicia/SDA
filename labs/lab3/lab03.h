#ifndef SD_LABS_LAB03_H
#define SD_LABS_LAB03_H

typedef struct node {
    int *data;
    struct node *next;
} node_t;

typedef struct sl_list {
    node_t *head;
    node_t *tail;
    size_t len;
} sl_list_t;

node_t *init_node(int *value);

void free_node(node_t *node);

sl_list_t *init_list();

void destroy_list(sl_list_t *list);

int insert_node(sl_list_t *list, int value, uint position);

int remove_node_by_key(sl_list_t *list, int value);

int remove_node_at_position(sl_list_t *list, uint position);

void print_list_int(sl_list_t *list);

int cyclic_search(sl_list_t *list, int k);

#endif //SD_LABS_LAB03_H
