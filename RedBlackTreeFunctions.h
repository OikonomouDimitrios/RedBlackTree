//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include "Node.h"

int getInsertValuesFromUser();

void insertNode(Node *rootNode) {
    Node newNode = initializeNewNode(getInsertValuesFromUser(), Red);
    Node y = nilNode;
    Node x = *rootNode;
    while (x != nilNode) {
        y = x;
        if (newNode->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    newNode->parent = y;
    if (y==nilNode){

    }
    //TODO IMPLEMENT
}

int getInsertValuesFromUser() {
    int x;
    printf("\ngive me a key:");
    scanf("%d", &x);
    return x;

}

void printTree(Node root) {
    //TODO IMPLEMENT
}

void deleteNode(Node *root) {
    //TODO IMPLEMENT
}

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
