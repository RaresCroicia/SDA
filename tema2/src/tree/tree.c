#include "tree.h"
#include "rgb.h"
#include "utils.h"
#include <stdlib.h>

Quadtree* quadtree_alloc(int index, unsigned char red, unsigned char green, unsigned char blue,
                        uint32_t area, int32_t top_left, 
                        int32_t top_right, int32_t bottom_right, int32_t bottom_left){
    Quadtree* this;
    this = (Quadtree*)malloc(sizeof(Quadtree));
    this->index = index;
    this->info = (QuadtreeNode*)malloc(sizeof(QuadtreeNode));
    this->info->area = area;
    this->info->red = red;
    this->info->green = green;
    this->info->blue = blue;
    this->info->top_left = top_left;
    this->info->top_right = top_right;
    this->info->bottom_left = bottom_left;
    this->info->bottom_right = bottom_right;

    return this;
}

Quadtree* create_quadtree(Quadtree* node, RGB** matrix, int startX, int startY, int width, int height, int factor){
    // Daca eroarea e mai mica sau egala decat toleranta, atunci nodul este frunza
    if(determinate_mean(matrix, startX, startY, width, height) <= factor){
        node->first = NULL;
        node->second = NULL;
        node->third = NULL;
        node->fourth = NULL;
        node->info->top_left = -1;
        node->info->top_right = -1;
        node->info->bottom_left = -1;
        node->info->bottom_right = -1;
    }
    else{
        node->first = quadtree_alloc(node->index * 4 + 1, 
                                    get_average_color(matrix, startX, startY, width/2, height/2).red,
                                    get_average_color(matrix, startX, startY, width/2, height/2).green,
                                    get_average_color(matrix, startX, startY, width/2, height/2).blue,
                                    (width/2) * (height/2), 
                                    (node->index * 4 + 1) * 4 + 1,
                                    (node->index * 4 + 1) * 4 + 2,
                                    (node->index * 4 + 1) * 4 + 3,
                                    (node->index * 4 + 1) * 4 + 4);
         
        node->second = quadtree_alloc(node->index * 4 + 2, 
                                    get_average_color(matrix, startX + width/2, startY, width/2, height/2).red,
                                    get_average_color(matrix, startX + width/2, startY, width/2, height/2).green,
                                    get_average_color(matrix, startX + width/2, startY, width/2, height/2).blue,
                                    (width/2) * (height/2), 
                                    (node->index * 4 + 2) * 4 + 1,
                                    (node->index * 4 + 2) * 4 + 2,
                                    (node->index * 4 + 2) * 4 + 3,
                                    (node->index * 4 + 2) * 4 + 4);   

        node->third = quadtree_alloc(node->index * 4 + 3, 
                                    get_average_color(matrix, startX + width/2, startY + height/2, width/2, height/2).red,
                                    get_average_color(matrix, startX + width/2, startY + height/2, width/2, height/2).green,
                                    get_average_color(matrix, startX + width/2, startY + height/2, width/2, height/2).blue,
                                    (width/2) * (height/2), 
                                    (node->index * 4 + 3) * 4 + 1,
                                    (node->index * 4 + 3) * 4 + 2,
                                    (node->index * 4 + 3) * 4 + 3,
                                    (node->index * 4 + 3) * 4 + 4);                  

        node->fourth = quadtree_alloc(node->index * 4 + 4, 
                                    get_average_color(matrix, startX, startY + height/2, width/2, height/2).red,
                                    get_average_color(matrix, startX, startY + height/2, width/2, height/2).green,
                                    get_average_color(matrix, startX, startY + height/2, width/2, height/2).blue,
                                    (width/2) * (height/2), 
                                    (node->index * 4 + 3) * 4 + 1,
                                    (node->index * 4 + 3) * 4 + 2,
                                    (node->index * 4 + 3) * 4 + 3,
                                    (node->index * 4 + 3) * 4 + 4);

        // Cream recursiv restul arborelui
        node->first = create_quadtree(node->first, matrix, startX, startY, width/2, height/2, factor);
        node->second = create_quadtree(node->second, matrix, startX + width/2, startY, width/2, height/2, factor);
        node->third = create_quadtree(node->third, matrix, startX + width/2, startY + height/2, width/2, height/2, factor);
        node->fourth = create_quadtree(node->fourth, matrix, startX, startY + height/2, width/2, height/2, factor);
    }
    return node;
}

void destroy_tree(Quadtree** node){
    if((*node)->first != NULL){
        destroy_tree(&(*node)->first);
        destroy_tree(&(*node)->second);
        destroy_tree(&(*node)->third);
        destroy_tree(&(*node)->fourth);
    }
    free((*node)->info);
    free((*node));
    *node = NULL;
}

int count_nodes(Quadtree* node){
    if(node == NULL)
        return 0;
    return 1 + count_nodes(node->first) + count_nodes(node->second) + count_nodes(node->third) + count_nodes(node->fourth); 
}

int isLeaf(Quadtree* node){
    return (node->first == NULL && node-> second == NULL && node->third == NULL && node->fourth == NULL);
}

int count_leaves(Quadtree* node){
    if(node == NULL)
        return 0;
    return isLeaf(node) + count_leaves(node->first) + count_leaves(node->second) + count_leaves(node->third) + count_leaves(node->fourth);
}

Quadtree* index_tree(Quadtree* root){
    Queue* coada = init_queue();
    enqueue(&coada, root);
    int index = 0;
    while(!empty(coada)){
        Quadtree* top = dequeue(&coada);
        top->index = index;
        if(top->first != NULL){
            enqueue(&coada, top->first);
            enqueue(&coada, top->second);
            enqueue(&coada, top->third);
            enqueue(&coada, top->fourth);
        }
        index ++;
    }
    free(coada);
    return root;
}

Quadtree* index_tree_children(Quadtree* root){
    Queue* coada = init_queue();
    enqueue(&coada, root);
    while(!empty(coada)){
        Quadtree* top = dequeue(&coada);
        if(top->first != NULL){
            top->info->top_left = top->first->index;
            top->info->top_right = top->second->index;
            top->info->bottom_right = top->third->index;
            top->info->bottom_left = top->fourth->index;
            enqueue(&coada, top->first);
            enqueue(&coada, top->second);
            enqueue(&coada, top->third);
            enqueue(&coada, top->fourth);
        }
        else{
            top->info->top_left = -1;
            top->info->top_right = -1;
            top->info->bottom_right = -1;
            top->info->bottom_left = -1;
        }
    }
    free(coada);
    return root;
}

QuadtreeNode* make_vector(Quadtree* root){
    Queue* coada = init_queue();
    enqueue(&coada, root);
    QuadtreeNode *vector = (QuadtreeNode*)malloc(sizeof(QuadtreeNode) * count_nodes(root));
    while(!empty(coada)){
        Quadtree* top = dequeue(&coada);
        vector[top->index] = *(top->info);
        if(top->first != NULL){
            enqueue(&coada, top->first);
            enqueue(&coada, top->second);
            enqueue(&coada, top->third);
            enqueue(&coada, top->fourth);
        }
    }
    free(coada);
    return vector;
}

void print_arbore(Quadtree* root){
    Queue* coada = init_queue();
    enqueue(&coada, root);
    while(!empty(coada)){
        Quadtree* top = dequeue(&coada);
        printf("Nodul cu index %d\n", top->index);
        printf("R: %d  G: %d  B: %d\n", top->info->red, top->info->green, top->info->blue);
        printf("Aria: %d\n", top->info->area);
        printf("Copiii: %d %d %d %d\n\n", top->info->top_left, top->info->top_right, top->info->bottom_right, top->info->bottom_left);
        if(top->first != NULL){
            enqueue(&coada, top->first);
            enqueue(&coada, top->second);
            enqueue(&coada, top->third);
            enqueue(&coada, top->fourth);
        }
    }
    free(coada);
}

Quadtree* create_quadtree_from_vector(QuadtreeNode* vector, int index){
    Quadtree *this = quadtree_alloc(index, vector[index].red, vector[index].green, vector[index].blue,
                                    vector[index].area, vector[index].top_left, vector[index].top_right,
                                    vector[index].bottom_right, vector[index].bottom_left);
    // Daca elementul din vector reprezinta o frunza din arbore, nu mai continuam recursivitatea
    if(vector[index].top_left == -1){
        this->first = NULL;
        this->second = NULL;
        this->third = NULL;
        this->fourth = NULL;
    }

    // Altfel, creem in mod recursiv pana la frunze
    else{
        this->first = create_quadtree_from_vector(vector, vector[index].top_left);
        this->second = create_quadtree_from_vector(vector, vector[index].top_right);
        this->third = create_quadtree_from_vector(vector, vector[index].bottom_right);
        this->fourth = create_quadtree_from_vector(vector, vector[index].bottom_left);
    }
    return this;
}

void print_vector(QuadtreeNode* vector, int length){
    for(int i = 0; i < length; i++){
        printf("NODUL %d\n\n", i);
        printf("R: %d  G: %d  B: %d\n", vector[i].red, vector[i].green, vector[i].blue);
    }
}

Queue* init_queue(){
    Queue* queue;
    queue = (Queue*) malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->len = 0;
    return queue;
}

QueueNode* queue_node_init(Quadtree* elem){
    QueueNode* this = (QueueNode*) malloc(sizeof(QueueNode));
    this->next = NULL;
    this->elem = elem;
    return this;
}

void enqueue(Queue** queue, Quadtree* elem){
    if((*queue)->len == 0){
        QueueNode *aux = queue_node_init(elem);
        (*queue)->head = aux;
        (*queue)->tail = aux;
        (*queue)->len = 1;
        return;
    }
    (*queue)->tail->next = queue_node_init(elem);
    (*queue)->tail = (*queue)->tail->next;
    ((*queue)->len)++;
}

Quadtree* dequeue(Queue** queue){ //sa nu uiti ca se apeleaza cu &
    QueueNode *cap = (*queue)->head;
    (*queue)->head = (*queue)->head->next;
    Quadtree *elem = cap->elem;
    free(cap);
    ((*queue)->len)--;
    if((*queue)->len == 1)
        (*queue)->tail = (*queue)->head;
    if((*queue)->len == 0)
        (*queue)->tail = (*queue)->head = NULL;
    return elem;
}

int empty(Queue* queue){
    return (queue->len == 0);
}

void swap_node(Quadtree** a, Quadtree** b){
    Quadtree* aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void horizontal_rotation(Quadtree** node){
    if((*node)->first != NULL){
        horizontal_rotation(&(*node)->first);
        horizontal_rotation(&(*node)->second);
        horizontal_rotation(&(*node)->third);
        horizontal_rotation(&(*node)->fourth);
        swap_node(&(*node)->first, &(*node)->second);
        swap_node(&(*node)->third, &(*node)->fourth);
    }
}

void vertical_rotation(Quadtree** node){
    if((*node)->first != NULL){
        vertical_rotation(&(*node)->first);
        vertical_rotation(&(*node)->second);
        vertical_rotation(&(*node)->third);
        vertical_rotation(&(*node)->fourth);
        swap_node(&(*node)->first, &(*node)->fourth);
        swap_node(&(*node)->second, &(*node)->third);
    }
}
