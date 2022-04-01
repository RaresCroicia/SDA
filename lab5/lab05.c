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

void radixSort(int *v, int n) {
    /*
     * TODO Exercitiul 4
     */
}





// {[([)]}