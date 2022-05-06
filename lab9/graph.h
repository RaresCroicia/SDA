#ifndef __graph__
#define __graph__

typedef struct graphMat{
    int nr_nodes;
    int **mat_adj;
}graph_mat;

typedef struct graphNode{
    struct graphNode *next;
    int ID_node;
}graph_node;

typedef struct graphList{
    graph_node **adj_list;
    int nr_nodes;
}graph_list;

graph_mat init_graph_mat(int nr_nodes);
graph_node* init_node(int j);
graph_list init_graph_list(int nr_nodes);
void add_edge_mat(graph_mat *G, int i, int j);
void delete_edge_mat(graph_mat *G, int i, int j);
int get_grad(graph_mat G, int i);
void free_graph_mat(graph_mat *G);
void print_matr_adj(graph_mat G);

void add_edge_list(graph_list *G, int i, int j);
void delete_edge_list(graph_list *G, int i, int j);
void print_list(graph_list G);
void free_graph_list(graph_list *G);


#endif