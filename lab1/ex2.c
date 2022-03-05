#include <stdio.h>
#include <stdlib.h>

int nrCif(int n, int c){
    if(n == 0)
        return 0;
    else if(n%10 < c)
        return 1 + nrCif(n/10, c);
    else
        return nrCif(n/10, c);
}

int main(){
    int nr = 123456, c = 6;
    printf("%d\n", nrCif(nr, c));
}