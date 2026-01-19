#include <stdio.h>
#include "main.h"

int main()
{
    printf("---------------------------------NEEEEEWWWW---------------------------:\n");
    struct Node *root = create_tree_file("data/countries.txt");
    inorder_traverse(root);
    free_tree(root);
    printf("---------------------------------END---------------------------:\n");
    return 0;
}