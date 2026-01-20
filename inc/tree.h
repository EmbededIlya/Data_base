#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    struct CountryData country;
    int key;
    int height;
    struct Node *left;
    struct Node *right;
};

enum SearchObject {
    SEARCH_BY_NAME,
    SEARCH_BY_POPULATION,
    SEARCH_BY_PHONECODE,
    SEARCH_BY_GDP,
    SEARCH_BY_AREA,
    SEARCH_BY_KEY   
};
// Find functions
struct Node *find_min(struct Node *node);
struct Node *find_max(struct Node *node);

// Height functions
int get_height(struct Node *N);
void update_height(struct Node *N);
int get_balance(struct Node *N);

// Rotation functions
void swap_nodes(struct Node *a, struct Node *b);
void right_rotate(struct Node **root);
void left_rotate(struct Node **root);
void right_left_rotate(struct Node **root);
void left_right_rotate(struct Node **root);
void balance_tree(struct Node **root);

// Node operations
struct Node *create_node(char *name, long population, char *phoneCode, double gdp, long area, int key);
struct Node *insert_node(struct Node *node, char *name, long population, char *phoneCode, double gdp, long area, int key);
struct Node *copy_values(struct Node *dest, struct Node *src);
struct Node *delete_node(struct Node *root, int key);

// Traversal
void inorder_traverse(struct Node *node);
void reverse_inorder_traverse(struct Node *node);

// Memory management
void free_tree(struct Node *node);

// Test function
void test_tree();

// File writing helper
static void write_tree_inorder(FILE *fp, struct Node *node);
#endif // TREE_H
