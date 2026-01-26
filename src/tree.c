
#include <tree.h>

/**
 * @brief Create a node object
 *
 * @param new_country
 * @param key
 * @return struct Node*
 */
struct Node *create_node(struct CountryData new_country, int key)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    if (!new_node)
        return NULL;
    new_node->country = new_country;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;
    return new_node;
}

struct Node *find_min(struct Node *root)
{
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;
    else
        return find_min(root->left);
}

struct Node *find_max(struct Node *root)
{
    if (root == NULL)
        return NULL;
    else if (root->right == NULL)
        return root;
    else
        return find_max(root->right);
}

int get_height(struct Node *N)
{
    return N ? N->height : -1;
}

void update_height(struct Node *N)
{
   if (N)
        N->height = 1 + fmax(get_height(N->left), get_height(N->right));
}

int get_balance(struct Node *N)
{
    return N == NULL ? 0 : get_height(N->left) - get_height(N->right);
}

struct Node *search_node(struct Node *root, int key)
{
    if (root == NULL)
        return NULL;
    if (key == root->key)
        return root;
    else if (key < root->key)
        return search_node(root->left, key);
    else
        return search_node(root->right, key);
}

void delete_tree(struct Node *root)
{
    if (root == NULL)
        return;
    delete_tree(root->right);
    delete_tree(root->left);
    free(root);
}

struct Node *right_rotate(struct Node *root)
{
    struct Node *left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
    update_height(root);
    update_height(left_child);
    return left_child;
}

struct Node *left_rotate(struct Node *root)
{
    struct Node *right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
    update_height(root);
    update_height(right_child);
    return right_child;
}

struct Node *balance_tree(struct Node *root)
{
    int balance = get_balance(root);
    if (balance > 1)
    {
        if (get_balance(root->left) < 0)
            root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1)
    {
        if (get_balance(root->right) > 0)
            root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

/* Insert a new node into the AVL tree */
struct Node *insert_node(struct Node *root, struct CountryData country, int key)
{
    if (root == NULL)
    {
        return create_node(country, key);
    }

    if (key < root->key)
    {
        if (root->left == NULL)
            root->left = create_node(country, key);
        else
            root->left = insert_node(root->left, country, key);
    }
    else if (key > root->key)
    {
        if (root->right == NULL)
            root->right = create_node(country, key);
        else
            root->right = insert_node(root->right, country, key);
    }
    update_height(root);
    return balance_tree(root);
}

struct Node *delete_node(struct Node *root, int key)
{
    if (root == NULL)
        return NULL;
    if (key < root->key)
    {
        root->left = delete_node(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = delete_node(root->right, key);
    }
    else
    {
        // Node without children
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL || root->right == NULL)
        {
            // Node with one children
             struct Node *tmp = root;
            root = (root->left) ? root->left : root->right;
            free(tmp);
        }
        else
        {
            // Node with two children
            struct Node *max_left = find_max(root->left);
            root->country = max_left->country;
            root->key = max_left->key;
            root->left = delete_node(root->left, max_left->key);
        }
    }
    if (root == NULL)
    {
        return NULL;
    }
    update_height(root);
    return balance_tree(root);
}

void inorder_traverse(struct Node *node)
{
     if (!node) return;
    inorder_traverse(node->left);
    printf("%d ", node->key);
    inorder_traverse(node->right);
}

void reverse_inorder_traverse(struct Node *node)
{
    if (!node)
        return;
    reverse_inorder_traverse(node->right);
    printf("Key %d Name %s GDP %.1f Population %ld Area %ld\n", node->key, node->country.name, node->country.gdp, node->country.population, node->country.area);
    reverse_inorder_traverse(node->left);
}

void inorder_array(struct Node *node, struct Node *arr, int *idx)
{
    if (!node) return;
    inorder_array(node->left, arr, idx);
    arr[*idx] = *node; // сохраняем текущую ноду
    printf("inorder_array %d\n", *idx);     
    (*idx)++;  

    inorder_array(node->right, arr, idx);
}

void print_inorder_array(struct Node **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]->key);
    }
    printf("\n");
}

void reverse_inorder_array(struct Node *node, struct Node *arr, int idx)
{
    if (!node) return;

    reverse_inorder_array(node->right, arr, idx);
    arr[idx] = *node;
    (idx)++;
    reverse_inorder_array(node->left, arr, idx);
}


struct Node * create_arr_nodes(int*size, struct Node *root)
{
    struct Node *arr = malloc((*size) * sizeof(struct Node));
    if (!arr) {
        printf("Memory allocation failed for array of nodes.\n");
        return NULL;
    }
    int idx = 0;
    inorder_array(root, arr, &idx);
    return arr;
}

/** Test function for the AVL tree implementation.*/



void test_tree(void)
{
    struct Node *root = NULL;

    // INSERT 50 ELEMENTS
    for (int i = 0; i < 50; i++)
    {
        struct CountryData c;

        snprintf(c.name, sizeof(c.name), "Country_%02d", i);
        snprintf(c.phoneCode, sizeof(c.phoneCode), "+%d", i);

        c.population = 1000000L + i * 50000;

        c.gdp = 10000.0 + i * 1000;
        c.area = 100000L + i * 1000;

        root = insert_node(root, c, i);
    }

    printf("Inorder traversal (sorted keys):\n");
    inorder_traverse(root);
    printf("\n");

    // DELETE HALF OF ELEMENTS
    for (int i = 0; i < 25; i++)
    {
        root = delete_node(root, i);
    }

    printf("After deleting keys 0..24:\n");
    inorder_traverse(root);
    printf("\n");

    delete_tree(root);
}
