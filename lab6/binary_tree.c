#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "queue.h"
#include "binary_tree.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define abs(a) \
   ({ __typeof__ (a) _a = (a); \
     _a > 0 ? _a : -_a; })

BTNode *initNode(int value) {
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));

    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->left = node->right = node->parent = NULL;

    return node;
}

void destroyTree(BTNode **root) {
    if (*root == NULL) {
        return;
    }

    // Sterg subarborele stang
    destroyTree(&(*root)->left);

    // Sterg subarborele drept
    destroyTree(&(*root)->right);

    // Sterg nodul curent
    free(*root);

    *root = NULL;
}

int isLeaf(BTNode *node) {
    return (node->left == NULL
            && node->right == NULL);
}

int getNodeDegrees(BTNode *node) {
    return (node->left != NULL) + (node->right != NULL);
}

BTNode *insertNode(BTNode *root, int value) {
    if(root == NULL){
        BTNode *act = initNode(value);
        root = act;
        return act;
    }
    else if(root->left == NULL && value <= root->data){
        BTNode *act = initNode(value);
        root->left = act;
        act->parent = root;
        return act;
    }
    else if(root->right == NULL && value >= root->data){
        BTNode *act = initNode(value);
        root->right = act;
        act->parent = root;
        return act;
    }
    else{
        if(value <= root->data)
            return insertNode(root->left, value);
        else
            return insertNode(root->right, value);
    }
}

BTNode *searchNode(BTNode *root, int value) {
    if(root == NULL)
        return NULL;
    else if(root->data == value)
        return root;
    else if(value < root->data)
        return searchNode(root->left, value);
    else
        return searchNode(root->right, value);
}


int removeNode(BTNode **root, BTNode *node) {
    if(isLeaf(node)){
        free(node);
        return 0;
    }

    if(getNodeDegrees(node) == 1){
        if(node == node->parent->left){
            if(node->left != NULL){
                node->left->parent = node->parent;
                node->parent->left = node->left;
                free(node);
            }
            else if(node->right != NULL){
                node->right->parent = node->parent;
                node->parent->left = node->right;
                free(node);
            }
        }
        else if(node == node->parent->right){
            if(node->left != NULL){
                node->left->parent = node->parent;
                node->parent->right = node->left;
                free(node);
            }
            else if(node->right != NULL){
                node->right->parent = node->parent;
                node->parent->right = node->right;
                free(node);
            }
        }
        return 0;
    }

    else{
        BTNode* aux = node;
        aux = node->right;
        while(aux->left != NULL)
            aux = aux->left;
        node->data = aux->data;
        aux->parent->left = NULL;
        aux->parent = NULL;
        free(aux);
        return 0;
    }

    return -1;
}

void printInOrder(BTNode *root) {
    if(root == NULL)
        return;
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

void printPreOrder(BTNode *root) {
    if(root == NULL)
        return;
    printf("%d ", root->data);    
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(BTNode *root) {
    if(root == NULL)
        return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

int getHeight(BTNode *root) {
    if(root == NULL)
        return 0;
    else
        return 1 + max(getHeight(root->left), getHeight(root->right));
}

int isBSTreeBalanced(BTNode *root) {
    if(root == NULL)
        return 1;
    if(abs(getHeight(root->left) - getHeight(root->right)) > 1){
        return 0;
    }
    else{
        return isBSTreeBalanced(root->left) && isBSTreeBalanced(root->right);
    }
    return 0;
}


