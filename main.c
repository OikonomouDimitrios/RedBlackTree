#include <stdio.h>
#include "Node.h"
#include "RedBlackTreeFunctions.h"

int main() {
    char c = '*';
    nullNode = initializeNullNode();
    root = nullNode;
    printf("\nThis program simulates a Red Black Tree\n");
    while (c != 'q') {
        printf("\n insert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            insertNode(&root);
        } else if (c == 'p') {
            printTree(root);
        } else if (c == 'd') {
            deleteNode(&root);
        }
    }
    return 0;
}
