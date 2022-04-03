#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab05.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

#define NUM_QUEUES 10

int checkBalancedBrackets(char *exp) {
    int len = strlen(exp);
    int status;
    int rez;
    stack_t *stack;
    stack = initList();
    for(int i = 0; i < len; i++){
        if(exp[i] == '{' || exp[i] == '[' || exp[i] == '(')
            push(stack, (int) exp[i]);
        else{
            if(exp[i] == ')'){
                if(top(stack, &status) == '(')
                    pop(stack, &status);
                else
                    return 0;
            }
            if(exp[i] == ']'){
                if(top(stack, &status) == '[')
                    pop(stack, &status);
                else
                    return 0;
            }
            if(exp[i] == '}'){
                if(top(stack, &status) == '{')
                    pop(stack, &status);
                else
                    return 0;
            }
        }
    }
    if(stack->head != NULL)
        return 0;
    return 1;
}

int getMaxDigits(int *v, int n){
    int max = v[0];
    for(int i = 1; i < n; i++)
        if(max < v[i])
            max = v[i];
    
    return countDigits(max);
}

int countDigits(int n){
    int cnt = 0;
    if(n == 0)
        return 1;
    while(n){
        cnt++;
        n /= 10;
    }
    return cnt;
}


void radixSort(int *v, int n) {
    int numar_iteratii = getMaxDigits(v, n);
    int status;
    queue_t *cozi_cifre[NUM_QUEUES];
    for(int i = 0; i < NUM_QUEUES; i++)
        cozi_cifre[i] = initList();
    int pow = 1;
    for(int i = 0; i < numar_iteratii; i++){
        for(int j = 0; j < n; j++)
            enqueue(cozi_cifre[(v[j]/pow)%10], v[j]);

        int poz = 0;
        for(int j = 0; j < NUM_QUEUES; j++){
            while(!is_empty(cozi_cifre[j]))
                v[poz++] = dequeue(cozi_cifre[j], &status);
        }
        pow *= 10;
    }
}





// {[([)]}