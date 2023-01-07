//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include "Node.h"

Node findNode(Node rootNode, int key);

int getValueFromUser();

void insertNodeFixup(Node *rootNode, Node z);

void leftRotate(Node *rootNode, Node x);

void rightRotate(Node *rootNode, Node y);

bool isLeftChild(Node node);

bool isRightChild(Node node);

Node TreeMinimum(Node pNode);

void deleteFixup(Node *rootNode, Node x);

void initializeBasicNodes() {
    nullNode = initializeNullNode();
    root = nullNode;
}

void insertNode(Node *rootNode) {
    Node newNode = initializeNewNode(getValueFromUser(), Red);
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
            if (z->parent != nullNode) {
                z->parent->parent->colour = Red;
                rightRotate(rootNode, z->parent->parent);
            }
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
            if (z->parent->parent != nullNode) {
                z->parent->parent->colour = Red;
                leftRotate(rootNode, z->parent->parent);
            }
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

int getValueFromUser() {
    int x;
    printf("\ngive me a key:");
    scanf("%d", &x);
    return x;

}

void printTree(Node x) {
    if (x != nullNode) {
        if (x->left != nullNode) {
            printTree(x->left);
        }
        printf("\n the key is :%d color is %s\n ", x->key, colours[x->colour]);
        if (x->right != nullNode) {
            printTree(x->right);
        }
    } else if (x == nullNode) {
        printf("\n There are no nodes to print\n");
    }
}


void transplant(Node *rootNode, Node u, Node v) {
    if (u->parent == nullNode) {
        (*rootNode) = v;
    } else if (isLeftChild(u)) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void deleteNode(Node *rootNode) {
    Node z = findNode(*rootNode, getValueFromUser());
    if (!z) {
        printf("No such key exists in RB Tree!\n");
        return;
    }
    Node y;
    Colour y_original_Colour = z->colour;
    Node x;
    if (z->left == nullNode) {
        x = z->right;
        transplant(rootNode, z, z->right);
    } else if (z->right == nullNode) {
        x = z->left;
        transplant(rootNode, z, z->left);
    } else {
        y = TreeMinimum(z->right);
        y_original_Colour = y->colour;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(rootNode, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(rootNode, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->colour = z->colour;
    }
    if (y_original_Colour == Black) {
        deleteFixup(rootNode, x);
    }
}

void deleteFixup(Node *rootNode, Node x) {
    while (x != *rootNode && x->colour == Black) {
        if (isLeftChild(x)) {
            Node w = x->parent->right;
            if (w->colour == Red) {
                w->colour = Black;
                x->parent->colour = Red;
                leftRotate(rootNode, x->parent);
                w = x->parent->right;
            }
            if (w->left->colour == Black && w->right->colour == Black) {
                w->colour = Red;
                x = x->parent;
            } else if (w->right->colour == Black) {
                w->left->colour = Black;
                w->colour = Red;
                rightRotate(rootNode, w);
                w = x->parent->right;
            }
            w->colour = x->parent->colour;
            x->parent->colour = Black;
            w->right->colour = Black;
            leftRotate(rootNode, x->parent);
            x = *rootNode;
        } else {
            // Same as then clause with "right" and "left" exchanged
            Node w = x->parent->left;
            if (w->colour == Red) {
                w->colour = Black;
                x->parent->colour = Red;
                rightRotate(rootNode, x->parent);
                w = x->parent->left;
            }
            if (w->right->colour == Black && w->left->colour == Black) {
                w->colour = Red;
                x = x->parent;
            } else if (w->left->colour == Black) {
                w->right->colour = Black;
                w->colour = Red;
                leftRotate(rootNode, w);
                w = x->parent->left;
            }
            w->colour = x->parent->colour;
            x->parent->colour = Black;
            w->left->colour = Black;
            rightRotate(rootNode, x->parent);
            x = *rootNode;
        }
    }
    x->colour = Black;
}

Node TreeMinimum(Node pNode) {
    while (pNode->left != nullNode) {
        return TreeMinimum(pNode->left);
    }
    return pNode;
}

Node findNode(Node rootNode, int key) {
    if (rootNode == NULL) return NULL;
    if (key == rootNode->key) return rootNode;
    if (key < rootNode->key) return findNode(rootNode->left, key);
    else return findNode(rootNode->right, key);
}

bool isLeftChild(Node node) {
    return node == node->parent->left;
}

bool isRightChild(Node node) {
    return node == node->parent->right;
}

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
