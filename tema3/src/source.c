#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "functions.h"
#include "utils.h"


int main(void){
    int nodes, edges, storages;
    int u, v;
    double w;
    int tasks;
    graph G;
    fscanf(stdin, "%d%d%d", &nodes, &edges, &storages);
    G = init_graph(nodes, storages); // initializam nodul si il construimm
    for(int i = 0; i < edges; i++){
        fscanf(stdin, "%d%d%lf", &u, &v, &w);
        add_node(&G, u, v, w);
    }
    for(int i = 0; i < storages; i++)
        fscanf(stdin, "%d", &G.storages[i]); // citim care noduri sunt depozite
    
    fscanf(stdin, "%d", &tasks);
    char task[3];
    for(int i = 0; i < tasks; i++){ // rezolvam fiecare task
        fscanf(stdin, "%s", task);
        if(!strcmp(task, "e1"))
            solve_e1(G);
        if(!strcmp(task, "e2"))
            solve_e2(G);
        if(!strcmp(task, "e3"))
            solve_e3(G);
        if(i != tasks-1)
            printf("\n");
    }
    free_graph(&G);
}