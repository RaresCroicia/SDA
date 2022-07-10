#include "functions.h"
#include "graph.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve_e1(graph G){ //drumul de cost minim
    int storage;
    int no_shops;
    int **next;
    double **dist;
    next = calloc(G.number_of_nodes, sizeof(int*));
    dist = calloc(G.number_of_nodes, sizeof(double*));
    for(int i = 0; i < G.number_of_nodes; i++){
        next[i] = calloc(G.number_of_nodes, sizeof(int));
        dist[i] = calloc(G.number_of_nodes, sizeof(double));
    }
    for(int i = 0; i < G.number_of_nodes; i++)
        for(int j = 0; j < G.number_of_nodes; j++){
            dist[i][j] = inf;
            next[i][j] = -1;
        }
    Floyd(G, &dist, &next);
    double cost_total = 0;
    fscanf(stdin, "%d", &storage);
    fscanf(stdin, "%d", &no_shops);
    for(int i = 0; i < no_shops; i++){
        int act_shop;
        fscanf(stdin, "%d", &act_shop);
        printf("%d\n", act_shop);
        printf("%0.1lf %0.1lf\n", dist[storage][act_shop], dist[act_shop][storage]);
        cost_total += dist[storage][act_shop] + dist[act_shop][storage];
        Path(G, storage, act_shop, next);
        printf(" ");
        Path(G, next[act_shop][storage], storage, next);
        printf("\n");
    }
    printf("%0.1lf", cost_total);
    for(int i = 0; i < G.number_of_nodes; i++){
        free(next[i]);
        free(dist[i]);
    }
    free(next);
    free(dist);
    
}

void solve_e2(graph G){ //numarul de componente tare conexe
    int *s, *d;
    int *ctc, nr_ctc = 0;
    s = calloc(G.number_of_nodes, sizeof(int));
    d = calloc(G.number_of_nodes, sizeof(int));
    ctc = calloc(G.number_of_nodes, sizeof(int));
    int *cnt_ctc = calloc(G.number_of_nodes + 1, sizeof(int));
    for(int i = 0; i < G.number_of_nodes; i++)
        ctc[i] = 0;
    for(int i = 0; i < G.number_of_nodes; i++){
        if(ctc[i] == 0 && !isStorage(G, i)){
            for(int j = 0; j < G.number_of_nodes; j++)
                s[j] = d[j] = 0;
            
            nr_ctc++;
            dfsE(G, i, &s);
            dfsI(G, i, &d);
            for(int j = 0; j < G.number_of_nodes; j++)
                if(s[j] == 1 && d[j] == 1 && !isStorage(G, j)){
                    ctc[j] = nr_ctc;
                    cnt_ctc[nr_ctc] ++;
                }
        }
    }

    printf("%d\n", nr_ctc);
    int cnt;
    for(int j = 1; j < nr_ctc; j++){
        cnt = 1;
        for(int i = 0; i < G.number_of_nodes; i++)
            if(ctc[i] == j && cnt < cnt_ctc[j]){
                printf("%d ", i);
                cnt++;
            }
            else if(ctc[i] == j && cnt == cnt_ctc[j])
                printf("%d\n", i);
    }
    cnt = 1;
    for(int i = 0; i < G.number_of_nodes; i++)
        if(ctc[i] == nr_ctc && cnt < cnt_ctc[nr_ctc]){
            printf("%d ", i);
            cnt++;
        }
        else if(ctc[i] == nr_ctc && cnt == cnt_ctc[nr_ctc])
            printf("%d", i);
    free(s);
    free(d);
    free(ctc);
    free(cnt_ctc);
}

void solve_e3(graph G){ //djikstra pe masti
    int zones;
    fscanf(stdin, "%d", &zones);
    for(int i = 0; i < zones; i++){
        int k;
        fscanf(stdin, "%d", &k);
        int *zone_houses = calloc(k, sizeof(int));
        for(int j = 0; j < k; j++)
            fscanf(stdin, "%d", &zone_houses[j]);
        double cost = inf;
        for(int j = 0; j < G.number_of_storages; j++)
            cost = min_double(cost, djikstra(G, j, zone_houses, k));
        printf("%0.1lf", cost);
        if(i != zones-1)
            printf("\n");
        free(zone_houses);
    }
}
