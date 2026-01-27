
#include <tree.h>

/**
 * @brief Create a node object
 *
 * @param new_country
 * @param key
 * @return struct Node*
 */
struct Node *create_node(struct CountryData new_country, unsigned long key)
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

struct Node *search_node(struct Node *root, unsigned long key)
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
struct Node *insert_node(struct Node *root, struct CountryData country, unsigned long key)
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

struct Node *delete_node(struct Node *root, unsigned long key)
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
    if (!node)
        return;
    inorder_traverse(node->left);
    writeCountryRow_console(&node->country);
    inorder_traverse(node->right);
}

void reverse_inorder_traverse(struct Node *node)
{
    if (!node)
        return;
    reverse_inorder_traverse(node->right);
    writeCountryRow_console(&node->country);
    reverse_inorder_traverse(node->left);
}

void inorder_array(struct Node *node, struct Node *arr, int *idx)
{
    if (!node)
        return;
    inorder_array(node->left, arr, idx);
    arr[*idx] = *node; // сохраняем текущую ноду
    // printf("inorder_array %d\n", *idx);
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
    if (!node)
        return;

    reverse_inorder_array(node->right, arr, idx);
    arr[idx] = *node;
    (idx)++;
    reverse_inorder_array(node->left, arr, idx);
}

struct Node *create_arr_nodes(int *size, struct Node *root)
{
    struct Node *arr = malloc((*size) * sizeof(struct Node));
    if (!arr)
    {
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

void print_node_co_data(const struct Node *node)
{
    if (!node)
    {
        printf("Node: NULL\n");
        return;
    }
    printf("  Country data:\n");
    printf("    name: %s\n", node->country.name);
    printf("    population: %ld\n", node->country.population);
    printf("    phoneCode: %s\n", node->country.phoneCode);
    printf("    gdp: %.2f\n", node->country.gdp);
    printf("    area: %ld\n", node->country.area);
}

int count_nodes(struct Node *node)
{
    if (!node)
        return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

void copy_tree_data(struct Node *node, struct CountryData *arr, int *idx)
{
    if (!node)
        return;
    copy_tree_data(node->left, arr, idx);
    arr[(*idx)++] = node->country;
    copy_tree_data(node->right, arr, idx);
}

struct Node *build_tree_with_keys(struct CountryData *arr, int size, CountryField mode_key)
{
    struct Node *new_root = NULL;
    for (int i = 0; i < size; i++)
    {
        unsigned long key = generate_key(mode_key, &arr[i]);
        new_root = insert_node(new_root, arr[i], key);
    }
    return new_root;
}

struct Node *rebuild_tree_with_new_keys(struct Node *root, CountryField mode_key)
{
    if (!root)
        return NULL;

    // Подсчёт размера дерева
    int size = count_nodes(root);

    // Копирование данных
    struct CountryData *arr = malloc(size * sizeof(struct CountryData));
    if (!arr)
        return NULL;
    int idx = 0;
    copy_tree_data(root, arr, &idx);

    // Удаление старого дерева
    delete_tree(root);

    // Создание нового дерева с новыми ключами
    struct Node *new_root = build_tree_with_keys(arr, size, mode_key);

    free(arr);
    return new_root;
}

void rebuild_filter_higher(struct Node *node, struct Node **new_root, CountryField mode_key, int value)
{
    if (!node)
        return;

    rebuild_filter_higher(node->left, new_root, mode_key, value);

    unsigned long key = generate_key(mode_key, &node->country);
    if (key > value)
    {
        *new_root = insert_node(*new_root, node->country, key);
    }
    rebuild_filter_higher(node->right, new_root, mode_key, value);
}

void rebuild_filter_lower(struct Node *node, struct Node **new_root, CountryField mode_key, int value)
{
    if (!node)
        return;
    rebuild_filter_lower(node->left, new_root, mode_key, value);
    unsigned long key = generate_key(mode_key, &node->country);
    if (key < value)
    {
        *new_root = insert_node(*new_root, node->country, key);
    }
    rebuild_filter_lower(node->right, new_root, mode_key, value);
}

struct Node *filter_tree(struct Node **new_root, struct Node *root, int value, int filter, CountryField mode_key)
{
    if (filter == 1)
    {
        rebuild_filter_lower(root, new_root, mode_key, value);
    }
    else if (filter == 2)
    {
        rebuild_filter_higher(root, new_root, mode_key, value);
    }
    else
    {
        printf("unknown_value");
    }
    reverse_inorder_traverse(*new_root);
    return *new_root;
}

// struct Node *rebuild_tree_filter_higher(struct Node *root, CountryField mode_key, int value)
// {
//     if (!root) return NULL;

//     // Подсчёт размера дерева
//     int size = count_nodes(root);
//     int i_internal = 0;
//     int need_value = 0;
//     // Копирование данных
//     struct CountryData *arr = malloc(size * sizeof(struct CountryData));
//     struct CountryData *arr_2 = malloc(size * sizeof(struct CountryData));
//     if (!arr || !arr_2) {
//     free(arr);
//     free(arr_2);
//     return NULL;
//     }
//     int idx = 0;
//     copy_tree_data(root, arr, &idx);

//     // Удаление старого дерева
//     delete_tree(root);
//     // Создание нового дерева с новыми ключами
//     for(int i = 0; i < size; i++){
//             if(generate_key(mode_key, &arr[i]) > value){
//                 arr_2[i_internal] = arr[i];
//                 i_internal++;
//             }
//         }
//     print_begin_file_table_con();
//     for (int i = 0; i < i_internal; i++)
//     {
//         writeCountryRow_console(&arr_2[i]);
//     }
//     struct Node *new_root = build_tree_with_keys(arr_2, i_internal, mode_key);
//     free(arr);
//     free(arr_2);
//     return new_root;
// }