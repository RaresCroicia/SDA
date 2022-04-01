#include <stdio.h>

int sumaPare(int *v, int left, int right){
    if(left == right){
        if(left%2 == 0)
            return v[left];
        else
            return 0;
    }
    int mid = left/2+right/2;
    int s1 = sumaPare(v, left, mid);
    int s2 = sumaPare(v, mid+1, right);
    return s1+s2;
}

int main(void){
    int v[] = {1, 2, 3, 4, 5};
    printf("%d\n", sumaPare(v, 0, 4));
}