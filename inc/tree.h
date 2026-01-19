#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char country[20];
    int country_id;
    int area;
    int VVP;
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};

// Find functions
struct Node* find_min(struct Node* node);
struct Node* find_max(struct Node* node);

// Height functions
int get_height(struct Node* N);
void update_height(struct Node* N);
int get_balance(struct Node* N);

// Rotation functions
void swap_nodes(struct Node* a, struct Node* b);
void right_rotate(struct Node** root);
void left_rotate(struct Node** root);
void right_left_rotate(struct Node** root);
void left_right_rotate(struct Node** root);
void balance_tree(struct Node** root);

// Node operations
struct Node* create_node(char* country, int country_id, int area, int VVP, int key);
struct Node* insert_node(struct Node* node, char* country, int country_id, int area, int VVP, int key);
struct Node* copy_values(struct Node* dest, struct Node* src);
struct Node* delete_node(struct Node* root, int key);

// Traversal
void inorder_traverse(struct Node* node);
void test_tree();
#endif
