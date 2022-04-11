//
// Created by florin on 4/4/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "stack.h"

#define PREFIX_MIDDLE            "├──\033[0;36mleft\033[0m───"
#define PREFIX_LAST              "└──\033[0;31mright\033[0m──"
#define PREFIX_MIDDLE_PARENT     "│         "
#define PREFIX_LAST_PARENT       "          "

#define NODE_TEXT()     \
    printf("\033[1;33m");

#define RESET_TEXT()    \
    printf("\033[0m");

static void prettyPrintUtil(BTNode *root, size_t depth, int is_right) {
    if (root == NULL) {
        return;
    }
    char *prefix;
    char *line = calloc(1000, 1);
    char *buf = calloc(1000, 1);
    char *buf2 = calloc(50, 1);
    BTNode *aux = root;

    if (depth == 0) {
        NODE_TEXT()
        printf("%d\n", root->data);
        RESET_TEXT()

        prettyPrintUtil(root->left, depth + 1, 0);
        prettyPrintUtil(root->right, depth + 1, 1);

        free(buf);
        free(buf2);
        free(line);
        return;
    }

    if (is_right) {
        prefix = PREFIX_LAST;
    } else {
        prefix = PREFIX_MIDDLE;
    }

    while (aux->parent != NULL && aux->parent->parent != NULL) {
        if (aux->parent->parent->right == aux->parent) {
            sprintf(buf, "%s", PREFIX_LAST_PARENT);
        } else {
            sprintf(buf, "%s", PREFIX_MIDDLE_PARENT);
        }
        // Copiez intr-o alta zona textul
        strcpy(buf2, line);

        // Suprascriu vechea linie
        memset(line, 0, strlen(line));
        strcpy(line, buf);

        // Adaug vechea linie peste noul prefix
        strcat(line, buf2);

        // Resetez buferele
        memset(buf, 0, strlen(buf));
        memset(buf2, 0, strlen(buf2));

        // Trec la urmatorul parinte
        aux = aux->parent;
    }
    printf("%s%s ", line, prefix);
    NODE_TEXT()
    printf("%d\n", root->data);
    RESET_TEXT()
    free(buf);
    free(buf2);
    free(line);

    prettyPrintUtil(root->left, depth + 1, 0);
    prettyPrintUtil(root->right, depth + 1, 1);
}

void prettyPrintTree(BTNode *root) {
    prettyPrintUtil(root, 0, 0);
}