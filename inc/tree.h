#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** Maximum length for country name and phone code */
#define MAX_NAME_LEN 64
#define MAX_PHONE_LEN 16

struct CountryData
{
    char name[100];     // Country name
    long population;    // Population
    char phoneCode[10]; // Phone code
    double gdp;         // GDP
    long area;          // Area
};

/** Structure for AVL tree node */
struct Node {
    struct CountryData country;
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

/** Function prototypes */

/* Node creation and basic operations */
struct Node *create_node(struct CountryData new_country, int key);
struct Node *find_min(struct Node *root);
struct Node *find_max(struct Node *root);
int get_height(struct Node *N);
void update_height(struct Node *N);
int get_balance(struct Node *N);

/* AVL tree operations */
struct Node *search_node(struct Node *root, int key);
struct Node *insert_node(struct Node *root, struct CountryData country, int key);
struct Node *delete_node(struct Node *root, int key);
struct Node *right_rotate(struct Node *root);
struct Node *left_rotate(struct Node *root);
struct Node *balance_tree(struct Node *root);

/* Tree deletion */
void delete_tree(struct Node *root);

/* Traversals */
void inorder_traverse(struct Node *node);
void reverse_inorder_traverse(struct Node *node);
void inorder_array(struct Node *node, struct Node *arr, int idx);
void reverse_inorder_array(struct Node *node, struct Node *arr, int idx);

/* Test function */
void test_tree(void);

#endif // TREE_H
