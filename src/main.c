#include <stdio.h>
#include "main.h"

int main()
{
    printf("---------------------------------NEEEEEWWWW---------------------------:\n");
    struct Node *root = create_tree_file("data/countries.txt", NAME);
    inorder_traverse(root);
    write_tree_pretty("data/countries.csv", root);
    free_tree(root);
    printf("---------------------------------END---------------------------:\n");
    return 0;
}



