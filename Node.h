//
// Created by DimitrisPhys_Desktop on 30/12/2022.
//

#ifndef REDBLACKTREE_NODE_H
#define REDBLACKTREE_NODE_H

#include <malloc.h>
#include "Constants.h"

typedef struct node *Node;
struct node {
    int key;
    Colour colour;
    Node left;
    Node right;
    Node parent;
};
Node root;

Node initializeNewNode(int key, Colour colour) {
    Node newRecord = (Node) malloc(sizeof(struct node));
    newRecord->key = key;
    newRecord->colour = colour ? colour : Red;
    newRecord->left = NULL;
    newRecord->right = NULL;
    newRecord->parent = NULL;
}

#endif //REDBLACKTREE_NODE_H
