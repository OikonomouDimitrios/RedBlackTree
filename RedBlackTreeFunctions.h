//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include "Node.h"

int getInsertValuesFromUser();

void insertNodeFixup(Node *rootNode, Node z);

void leftRotate(Node *rootNode, Node x);

void rightRotate(Node *rootNode, Node y);

bool isLeftChild(Node node);

bool isRightChild(Node node);

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


void rightRotate(Node *rootNode, Node y) {
    Node x = y->left;
    y->left = x->right;
    if (x->right != nullNode) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullNode) {
        (*rootNode) = x;
    } else if (isLeftChild(y)) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void leftRotate(Node *rootNode, Node x) {
//The pseudocode for LEFT-ROTATE assumes that x.right is not T.nil and that the
//root’s parent is T.nil.
    Node y = x->right;
    x->right = y->left;
    if (y->left != nullNode) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullNode) {
        (*rootNode) = y;
    } else if (isLeftChild(x)) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

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

bool isLeftChild(Node node) {
    return node == node->parent->left;
}

bool isRightChild(Node node) {
    return node == node->parent->right;
}

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
