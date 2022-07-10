#include "graph.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

graph init_graph(int no_nodes, int no_storages){
    graph G;
    G.adj_list = malloc(sizeof(graph_node*) * no_nodes);
    for(int i = 0; i < no_nodes; i++)
        G.adj_list[i] = NULL;
    G.number_of_nodes = no_nodes;
    G.number_of_storages = no_storages;
    G.storages = malloc(sizeof(int) * no_storages);
    return G;
}

graph_node* init_node(int j, double cost){
    graph_node *this = malloc(sizeof(graph_node));
    this->destination = j;
    this->price = cost;
    this->next = NULL;
    return this;
}

void add_node(graph *G, int i, int j, double cost){
    if(G->adj_list[i] == NULL)
        G->adj_list[i] = init_node(j, cost);
    else{
        graph_node *aux;
        for(aux = G->adj_list[i]; aux->next != NULL; aux = aux->next);
        graph_node *this = init_node(j, cost);
        aux->next = this;
    }
}

void print_graph(graph G){
    for(int i = 0; i < G.number_of_nodes; i++)
        print_node_adj(G, i);
    printf("Storages: ");
    for(int i = 0; i < G.number_of_storages; i++)
        printf("%d ", G.storages[i]);
    printf("\n");
}

void print_node_adj(graph G, int index){
    graph_node *aux = G.adj_list[index];
    printf("Nodul %d are copii: ", index);
    while(aux != NULL){
        printf("(%d, %0.1lf) ", aux->destination, aux->price);
        aux = aux->next;
    }
    printf("\n");
}

void free_node(graph_node** node){
    graph_node *aux = *node;
    while(aux != NULL){
        graph_node *act = aux;
        aux = aux->next;
        act->next = NULL;
        free(act);
    }
}

void free_graph(graph *G){
    for(int i = 0; i < G->number_of_nodes; i++)
        free_node(&G->adj_list[i]);
    free(G->adj_list);
    free(G->storages);
}

bool isEdge(graph G, int i, int j, double *cost){
    graph_node *aux = G.adj_list[i];
    if(aux == NULL)
        return FALSE;
    while(aux != NULL){
        if(aux->destination == j){
            *cost = aux->price;
            return TRUE;
        }
        aux = aux->next;
    }
    return FALSE;
}

bool isStorage(graph G, int node){
    for(int i = 0; i < G.number_of_storages; i++)
        if(G.storages[i] == node)
            return TRUE;
    return FALSE;
}

void dfsE(graph G, int node, int **s){
    (*s)[node] = 1;
    double cost;
    for(int i = 0; i < G.number_of_nodes; i++)
        if((*s)[i] == 0 && isEdge(G, node, i, &cost) && !isStorage(G, i))
            dfsE(G, i, s);
}

void dfsI(graph G, int node, int **d){
    (*d)[node] = 1;
    double cost;
    for(int i = 0; i < G.number_of_nodes; i++)
        if((*d)[i] == 0 && isEdge(G, i, node, &cost) && !isStorage(G, i))
            dfsI(G, i, d);
}

void Floyd(graph G, double ***dist, int ***next){
    for(int i = 0; i < G.number_of_nodes; i++)
        for(int j = 0; j < G.number_of_nodes; j++){
            double cost;
            if(isEdge(G, i, j, &cost)){
                (*dist)[i][j] = cost;
                (*next)[i][j] = j;
            }
            (*dist)[j][j] = 0;
            (*next)[j][j] = j;
        }
    
    for(int k = G.number_of_nodes-1; k >= 0; k--)
        for(int i = G.number_of_nodes-1; i >= 0; i--)
            for(int j = G.number_of_nodes-1; j >= 0; j--)
                if((*dist)[i][j] > (*dist)[i][k] + (*dist)[k][j]){
                    (*dist)[i][j] = (*dist)[i][k] + (*dist)[k][j];
                    (*next)[i][j] = (*next)[i][k];
                }
}

void Path(graph G, int i, int j, int **next){
    if(next[i][j] == -1)
        return;
    printf("%d", i);
    while(i != j){
        printf(" ");
        i = next[i][j];
        printf("%d", i);
    }
}

double djikstra(graph G, int storage_index, int* houses, int n_h){
    Queue *Q = init_queue();
    list lista = init_list();
    double min_cost = inf;
    enqueue(&Q, storage_index, 1, 0); // Adaugam depozitul de unde plecam cu starea sa
    while(!is_empty(Q)){
        nod_djikstra* this = dequeue(&Q);
        add_to_list(&lista, this->nod, this->mask, this->sum); // Adaugam nodul vizitat in lista

        /**
         * Daca am gasit un drum, ii retinem disttannta daca 
         * e mai mica decat a drumului gasit anterior
         */
        if(this->mask == (1<<(n_h+1))-1 && this->nod == storage_index){
            min_cost = min_double(min_cost, this->sum); 
            free(this);
            continue;
        }

        // Adaugam toti vecinii din zona la care exista drum in coada
        double aux_cost;
        for(int i = 0; i < G.number_of_nodes; i++)
            if(is_from_zone(houses, n_h, i)){
                if(isEdge(G, this->nod, i, &aux_cost)){
                    int index_mask = get_index_zone(houses, n_h, i)+1;
                    if(!is_visited(lista, i, this->mask | (1 << index_mask)))
                        enqueue(&Q, i, this->mask | (1 << index_mask), this->sum + aux_cost);
                }
            }
            else if(isStorage(G, i)){
                if(isEdge(G, this->nod, i, &aux_cost) && !is_visited(lista, i, this->mask))
                    enqueue(&Q, i, this->mask, this->sum + aux_cost);
            }
        free(this);
    }
    
    // Eliberam memoria
    free_queue(&Q);
    list_node *aux = lista.head;
    while(aux){
        list_node *auxx = aux;
        aux = aux->next;
        free(auxx->info);
        auxx->next = NULL;
        free(auxx);
    }

    return min_cost;
}