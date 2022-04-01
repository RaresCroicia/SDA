#include <stdio.h>
#include <stdlib.h>

int sum(int *v, int k, int n){
    int size = k;
    int s = 0;
    for(int i = 0; i < size; i++)
        s += v[i];
    return s;
}
void print(int *v, int k){
    int size = k;
    for(int i = 0; i < size; i++)
        printf("%d ", v[i]);
    printf("\n");
}


int bkt(int *v, int k, int n){
    if(sum(v, k, n) == n)
        print(v, k);
    else
        for(int i = 1; i <= n; i++){
            v[k] = i;
            if (sum(v, k, n) <= n && v[k] >= v[k-1]) bkt(v, k+1, n);
        }
}

int main(void){
    int n = 5;
    int *v = malloc(n * sizeof(int));
    bkt(v, 0, n);
}