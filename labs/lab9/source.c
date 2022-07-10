#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    int n_nodes, n_edges;
    fscanf(stdin, "%d%d", &n_nodes, &n_edges);

    
    graph_mat GMat = init_graph_mat(n_nodes);
    graph_list GList = init_graph_list(n_nodes);
    for(int i = 0; i < n_edges; i++){
        int u, v;
        fscanf(stdin, "%d%d", &u, &v);
        add_edge_mat(&GMat, u, v);
        add_edge_list(&GList, u, v);
    }

    // Functiile de la mat de adj
    printf("Implementarea cu matrice:\n");
    print_matr_adj(GMat);
    printf("\n");
    printf("Gradul lui 2: %d\nSterg legatura (2,4)...\n", get_grad(GMat, 2));
    delete_edge_mat(&GMat, 2, 4);
    printf("Gradul lui 2 dupa delete: %d\n", get_grad(GMat, 2));
    printf("\n");
    print_matr_adj(GMat);
    //free_graph_mat(&GMat);

    printf("\n");

    printf("Implementarea cu liste:\n");
    print_list(GList);
    printf("\n");
    printf("Gradul lui 2: %d\nSterg legatura (2,4)...\n", get_grad_list(GList, 2));
    delete_edge_list(&GList, 2, 4);
    printf("Gradul lui 2 dupa delete: %d\n", get_grad_list(GList, 2));
    printf("\n");
    print_list(GList);
    add_edge_mat(&GMat, 2, 4);

    // Parcurgerile
    int *visited;
    visited = calloc(n_nodes, sizeof(int));
    set_zeros(&visited, n_nodes);
    printf("Parcurgerea in adancime pornind din nodul 3: ");
    dfs(GMat, 3, &visited);
    printf("\n");
    set_zeros(&visited, n_nodes);
    printf("Parcurgerea in latime pornind din nodul 3: ");
    bfs(GMat, 3, &visited);
    printf("\n");
    set_zeros(&visited, n_nodes);
    
    // Verificarea existentei ciclurilor

    printf("%s", has_cycle(GMat, &visited) ? "Exista ciclu\n" : "Nu exista ciclu\n");

}