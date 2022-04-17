//
// Created by florin on 4/14/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"


trieNode_t *trieInitNode() {
    trieNode_t *newNode = malloc(sizeof(trieNode_t));

    // Initializez toti copiii la NULL
    newNode->children = calloc(NUM_CHILDREN, sizeof(trieNode_t *));

    // Setez acest nod ca nefiind sfarsit de cuvant
    newNode->isWordTerminal = 0;

    // Setez parintele la NULL
    newNode->parent = NULL;

    return newNode;
}

void trieFreeNode(trieNode_t *node) {
    free(node->children);
    free(node);
}

void trieDestroy(trieNode_t **root) {
    if (*root == NULL) {
        return;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        trieDestroy(&(*root)->children[i]);
    }
    trieFreeNode(*root);
    *root = NULL;
}

int trieNodeIsLeaf(trieNode_t *node) {
    if (node == NULL) {
        return 1;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            // Nodul are cel putin un copil
            return 0;
        }
    }
    // Nodul este frunza
    return 1;
}

void printNodeCharacters(trieNode_t *node) {
    if (node == NULL) {
        return;
    }

    printf("Nodul de la adresa %p are legaturi catre: ", node);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            printf("%c ", IDX_TO_CHAR(i));
        }
    }
    printf("\n");
}

void trieInsertWord(trieNode_t **root, char *word) {
    if(*root == NULL){
        *root = trieInitNode();
    }
    trieNode_t *aux = *root;
    while(*word != '\0'){
        if(aux->children[CHAR_TO_IDX(*word)] != NULL){
            aux = aux->children[CHAR_TO_IDX(*word)];
            word = word+1;
            continue;
        }
        trieNode_t *curr = trieInitNode();
        curr->parent = aux;
        aux->children[CHAR_TO_IDX(*word)] = curr;
        aux = curr;
        word = word+1;
    }
    aux->isWordTerminal = TRUE;
    return;
}

int trieContainsWord(trieNode_t *root, char *word) {
    if(root == NULL)
        return FALSE;
    trieNode_t *aux = root;
    while(*word != '\0'){
        if(aux->children[CHAR_TO_IDX(*word)] == NULL)
            return FALSE;
        aux = aux->children[CHAR_TO_IDX(*word)];
        word = word+1;
    }
    if(aux->isWordTerminal == TRUE)
        return TRUE;
    return FALSE;
}

void trieDeleteWord(trieNode_t **root, char *word) {
    if(root == NULL)
        return;
    
    trieNode_t *root_copy = *root;

    while(*word != '\0'){
        if(root_copy->children[CHAR_TO_IDX(*word)] == NULL)
            return;
        root_copy = root_copy->children[CHAR_TO_IDX(*word)];
        word = word+1;
    }
    root_copy->isWordTerminal = FALSE;
    root_copy = root_copy->parent;
    while(trieNodeIsLeaf(root_copy)){
        trieNode_t *prev = root_copy->parent;
        trieFreeNode(root_copy);
        root_copy = prev;
    }
}


void triePrefixMatching(trieNode_t *root, char *prefix) {
    // TODO
}



