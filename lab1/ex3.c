#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrom(char *s, int left, int right){
    if(left >= right)
        return 1;
    else if (s[left] != s[right])
        return 0;
    else
        return isPalindrom(s, left+1, right-1);

}

int main(){
    char s[] = "abccedcba";
    printf("%d\n", isPalindrom(s, 0, strlen(s)-1));
}