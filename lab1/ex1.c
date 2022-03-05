#include <stdio.h>
#include <stdlib.h>

int fibo(int n){
    if(n < 2) return 1;
    else
        return fibo(n-1) + fibo(n-2);
}


int main(){
    int n = 4;
    printf("%d\n", fibo(n));
}