#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    int n_nodes, n_edges;
    fscanf(stdin, "%d%d", &n_nodes, &n_edges);
    graph_mat GMat = init_graph_mat(n_nodes);
    for(int i = 0; i < n_edges; i++){
        int u, v;
        fscanf(stdin, "%d%d", &u, &v);
        add_edge_mat(&GMat, u, v);
    }
    print_matr_adj(GMat);
    delete_edge_mat(&GMat, 2, 4);
    printf("\n");
    print_matr_adj(GMat);
    free_graph_mat(&GMat);

    graph_list GList = init_graph_list(n_nodes);
    for(int i = 0; i < n_edges; i++){
        int u, v;
        fscanf(stdin, "%d%d", &u, &v);
        add_edge_list(&GList, u, v);
    }
    print_list(GList);
    delete_edge_list(&GList, 2, 4);
    printf("\n");
    print_list(GList);

}