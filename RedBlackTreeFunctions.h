//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include "Node.h"

int getInsertValuesFromUser();

void insertNodeFixup(Node *rootNode, Node z);

void leftRotate(Node *rootNode, Node z);

void rightRotate(Node *rootNode, Node z);

void insertNode(Node *rootNode) {
    Node newNode = initializeNewNode(getInsertValuesFromUser(), Red);
    Node y = nullNode;
    Node x = *rootNode;
    while (x != nullNode) {
        y = x;
        if (newNode->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    newNode->parent = y;
    if (y == nullNode) {
        (*rootNode) = newNode;
    } else if (newNode->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    insertNodeFixup(&root, newNode);
}

void insertNodeFixup(Node *rootNode, Node z) {
    Node aux;
    while (z->parent->colour == Red) {
        if (z->parent == z->parent->parent->left) {
            aux = z->parent->parent->right;
            if (aux->colour == Red) {
                z->parent->colour = Black;
                aux->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else if (z == z->parent->right) {
                z = z->parent;
                leftRotate(rootNode, z);
            }
            z->parent->colour = Black;
            z->parent->parent->colour = Red;
            rightRotate(rootNode, z->parent->parent);
        } else {
            aux = z->parent->parent->left;
            if (aux->colour == Red) {
                z->parent->colour = Black;
                aux->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else if (z == z->parent->left) {
                z = z->parent;
                rightRotate(rootNode, z);
            }
            z->parent->colour = Black;
            z->parent->parent->colour = Red;
            leftRotate(rootNode, z->parent->parent);
        }
    }
    (*rootNode)->colour = Black;
}

void rightRotate(Node *rootNode, Node z) {

}

void leftRotate(Node *rootNode, Node z) {
//The pseudocode for LEFT-ROTATE assumes that x.right is not T.nil and that the
//root’s parent is T.nil.
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
