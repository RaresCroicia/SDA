#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *v, int x, int left, int right){
    int mid = (left+right)/2;
    if(v[mid] == x)
        return mid;
    else if(left > right)
        return -1;
    else if(v[mid] < x)
        return binarySearch(v, x, mid+1, right);
    else
        return binarySearch(v, x, left, mid-1);
}

int main(){
    int v[] = {1, 2, 3, 4, 5};
    printf("%d\n", binarySearch(v, 6, 0, 4));


}