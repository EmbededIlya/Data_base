
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
    if (*root == NULL)
        return;

    int balance = get_balance(*root);

    // Left Heavy
    if (balance < -1)
    {
        if (get_balance((*root)->left) > 0)
            left_rotate(&((*root)->left)); // Left-Right case
        right_rotate(root);                // Left-Left case
    }
    // Right Heavy
    else if (balance > 1)
    {
        if (get_balance((*root)->right) < 0)
            right_rotate(&((*root)->right)); // Right-Left case
        left_rotate(root);                   // Right-Right case
    }
}

struct Node *create_node(char *name, long population, char *phoneCode, double gdp, long area, int key)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    strncpy(new_node->name, name, 99);
    new_node->name[99] = '\0';
    new_node->population = population;
    strncpy(new_node->phoneCode, phoneCode, 9);
    new_node->phoneCode[9] = '\0';
    new_node->gdp = gdp;
    new_node->area = area;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

struct Node *insert_node(struct Node *node, char *name, long population, char *phoneCode, double gdp, long area, int key)
{
    if (node == NULL)
        return create_node(name, population, phoneCode, gdp, area, key);

    if (key < node->key)
        node->left = insert_node(node->left, name, population, phoneCode, gdp, area, key);
    else if (key > node->key)
        node->right = insert_node(node->right, name, population, phoneCode, gdp, area, key);

    update_height(node);
    balance_tree(&node);
    return node;
}
struct Node *copy_values(struct Node *dest, struct Node *src)
{
    if (dest == NULL || src == NULL)
        return dest;
    strncpy(dest->name, src->name, 99);
    dest->name[99] = '\0';
    dest->population = src->population;
    strncpy(dest->phoneCode, src->phoneCode, 9);
    dest->phoneCode[9] = '\0';
    dest->gdp = src->gdp;
    dest->area = src->area;
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
    printf("Country: %s, Population: %ld, Phone: %s, GDP: %.2f, Area: %ld, Key: %d\n",
           node->name, node->population, node->phoneCode, node->gdp, node->area, node->key);
    inorder_traverse(node->right);
}

void reverse_inorder_traverse(struct Node *node)
{
    if (node == NULL)
        return;
    reverse_inorder_traverse(node->right);
    printf("Country: %s, Population: %ld, Phone: %s, GDP: %.2f, Area: %ld, Key: %d\n",
           node->name, node->population, node->phoneCode, node->gdp, node->area, node->key);
    reverse_inorder_traverse(node->left);
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
    root = insert_node(root, "CountryA", 1000000, "+1", 15000.0, 1000000, 10);
    root = insert_node(root, "CountryB", 2000000, "+2", 20000.0, 2000000, 20);
    root = insert_node(root, "CountryC", 1500000, "+3", 18000.0, 1500000, 5);

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