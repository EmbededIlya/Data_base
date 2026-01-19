
#include <tree.h>

struct Node *find_min(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
struct Node *find_max(struct Node *node)
{
    struct Node *current = node;
    while (current->right != NULL)
        current = current->right;
    return current;
}
int get_height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
void update_height(struct Node *N)
{
    if (N != NULL)
    {
        int left_height = get_height(N->left);
        int right_height = get_height(N->right);
        N->height = (left_height > right_height ? left_height : right_height) + 1;
    }
}
int get_balance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return get_height(N->right) - get_height(N->left);
}
void swap_nodes(struct Node *a, struct Node *b)
{
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}
void right_rotate(struct Node **root)
{
    swap_nodes(*root, (*root)->left);
    struct Node *old_right = (*root)->right;
    (*root)->right = (*root)->left;
    (*root)->left = (*root)->right->left;
    (*root)->right->left = (*root)->right->right;
    (*root)->right->right = old_right;
    update_height((*root)->left);
    update_height(*root);
}
void left_rotate(struct Node **root)
{
    swap_nodes(*root, (*root)->right);
    struct Node *old_left = (*root)->left;
    (*root)->left = (*root)->right;
    (*root)->right = (*root)->left->right;
    (*root)->left->right = (*root)->left->left;
    (*root)->left->left = old_left;
    update_height((*root)->right);
    update_height(*root);
}
void right_left_rotate(struct Node **root)
{
    left_rotate(&((*root)->right));
    right_rotate(root);
}
void left_right_rotate(struct Node **root)
{
    right_rotate(&((*root)->right));
    left_rotate(root);
}
void balance_tree(struct Node **root)
{
    int balance = get_balance(*root);
    if (balance < -1)
    {
        if (get_balance((*root)->left) <= 0)
        {
            right_rotate(root);
        }
        else
        {
            left_right_rotate(root);
        }
    }
    else if (balance > 1)
    {
        if (get_balance((*root)->right) >= 0)
        {
            left_rotate(root);
        }
        else
        {
            right_left_rotate(root);
        }
    }
}

struct Node *create_node(char *country, int country_id, int area, int VVP, int key)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    strncpy(new_node->country, country, 20);
    new_node->country_id = country_id;
    new_node->area = area;
    new_node->VVP = VVP;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

struct Node *insert_node(struct Node *node, char *country, int country_id, int area, int VVP, int key)
{
    if (node == NULL)
        return create_node(country, country_id, area, VVP, key);
    if (key < node->key)
        node->left = insert_node(node->left, country, country_id, area, VVP, key);
    else if (key > node->key)
        node->right = insert_node(node->right, country, country_id, area, VVP, key);
    update_height(node);
    balance_tree(&node);
    return node;
}
struct Node *copy_values(struct Node *dest, struct Node *src)
{
    if (dest == NULL || src == NULL)
        return dest;
    strncpy(dest->country, src->country, 20);
    dest->country_id = src->country_id;
    dest->area = src->area;
    dest->VVP = src->VVP;
    dest->key = src->key;
    return dest;
}
struct Node *delete_node(struct Node *root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct Node *temp = (root->left != NULL) ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            struct Node *temp = find_min(root->right);
            root = copy_values(root, temp);
            root->right = delete_node(root->right, temp->key);
        }
    }
    if (root != NULL)
    {
        update_height(root);
        balance_tree(&root);
    }
    return root;
}

void inorder_traverse(struct Node *node)
{
    if (node == NULL)
        return;
    inorder_traverse(node->left);
    printf("Country: %s, Key: %d\n", node->country, node->key);
    inorder_traverse(node->right);
}

void free_tree(struct Node *node)
{
    if (node == NULL)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void test_tree()
{
    struct Node *root = NULL;

    // Добавляем страны
    root = insert_node(root, "CountryA", 1, 1000, 50000, 10);
    root = insert_node(root, "CountryB", 2, 2000, 60000, 20);
    root = insert_node(root, "CountryC", 3, 1500, 55000, 5);

    printf("Tree after adding:\n");
    inorder_traverse(root);

    // Удаляем узел
    root = delete_node(root, 10);

    printf("\nTree after deletion:\n");
    inorder_traverse(root);

    // Освобождаем память
    // Нужно добавить функцию free_tree в tree.c/tree.h
    free_tree(root);
}