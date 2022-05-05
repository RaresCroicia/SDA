#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

graph_mat init_graph_mat(int nr_nodes){
    graph_mat G;
    G.nr_nodes = nr_nodes;
    G.mat_adj = calloc(nr_nodes, sizeof(int*));
    for(int i = 0; i < nr_nodes; i++)
        G.mat_adj[i] = calloc(nr_nodes, sizeof(int));
    return G;
}

graph_node* init_node(int j){
    graph_node *node;
    node = calloc(1, sizeof(graph_node));
    node->ID_node = j;
    node->next = NULL;
    return node;
}

graph_list init_graph_list(int nr_nodes){
    graph_list G;
    G.nr_nodes = nr_nodes;
    G.adj_list = calloc(nr_nodes, sizeof(graph_node*));
    return G;
}

void add_edge_mat(graph_mat *G, int i, int j){
    G->mat_adj[i][j] = 1;
    G->mat_adj[j][i] = 1;
}

void delete_edge_mat(graph_mat *G, int i, int j){
    G->mat_adj[i][j] = 0;
    G->mat_adj[j][i] = 0;
}

int get_grad(graph_mat G, int i){
    int grad = 0;
    for(int j = 0; j < G.nr_nodes; j++)
        grad += G.mat_adj[i][j];
    return grad;
}

void free_graph_mat(graph_mat *G){
    for(int i = 0; i < G->nr_nodes; i++)
        free(G->mat_adj[i]);
    free(G->mat_adj);
}

void print_matr_adj(graph_mat G){
    for(int i = 0; i < G.nr_nodes; i++){
        for(int j = 0; j < G.nr_nodes; j++)
            printf("%d ", G.mat_adj[i][j]);
        printf("\n");
    }
}

void add_edge_list(graph_list *G, int i, int j){
    graph_node *aux;
    if(G->adj_list[i] == NULL){
        G->adj_list[i] = init_node(j);
    }
    else{
        for(aux = G->adj_list[i]; aux->next != NULL; aux = aux->next);
        aux->next = init_node(j); 
    }
    
    if(G->adj_list[j] == NULL){
        G->adj_list[j] = init_node(i);
    }
    else{
        for(aux = G->adj_list[j]; aux->next != NULL; aux = aux->next);
        aux->next = init_node(i); 
    }
}

void delete_edge_list(graph_list *G, int i, int j){
    if(G->adj_list[i] == NULL)
        return;
    graph_node *aux;
    if(G->adj_list[i]->next == NULL && G->adj_list[i]->ID_node == j)
        G->adj_list[i] = NULL;
    else{
        aux = G->adj_list[i];
        if(aux->ID_node != j){
            while(aux->next != NULL){
                if(aux->next->ID_node == j)
                    break;
                aux = aux->next;
            }
            if(aux != NULL){
                graph_node *this = aux->next;
                aux->next = this->next;
                this->next = NULL;
                free(this);
            }
        }
        else{
            graph_node *this = G->adj_list[j];
            G->adj_list[j] = G->adj_list[j]->next;
            free(this);
        }
    }
    

    if(G->adj_list[j]->next == NULL && G->adj_list[j]->ID_node == i)
        G->adj_list[j] = NULL;
    else{
        aux = G->adj_list[j];
        if(aux->ID_node != i){
                while(aux->next != NULL){
                    if(aux->next->ID_node == i)
                        break;
                    aux = aux->next;
            }
            if(aux != NULL){
                graph_node *this = aux->next;
                aux->next = this->next;
                this->next = NULL;
                free(this);
            }
        
        }
        else{
            graph_node *this = G->adj_list[j];
            G->adj_list[j] = G->adj_list[j]->next;
            free(this);
        }
    }
}

// 1: 0 3 4 5

void print_list(graph_list G){
    for(int i = 0; i < G.nr_nodes; i++){
        printf("%d: ", i);
        graph_node *aux;
        for(aux = G.adj_list[i]; aux != NULL; aux = aux->next)
            printf("%d ", aux->ID_node);
        printf("\n");
    }
}

void free_graph_list(graph_list *G){
    for(int i = 0; i < G->nr_nodes; i++){
        graph_node *aux = G->adj_list[i];
        while(aux != NULL){
            graph_node *this = aux;
            aux = aux->next;
            this->next = NULL;
            free(this);
        }
    }
}




