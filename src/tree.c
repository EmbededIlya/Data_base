#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>

/* ===================== ПОИСК МИНИМУМА / МАКСИМУМА ===================== */

struct Node *find_min(struct Node *node)
{
    struct Node *current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

struct Node *find_max(struct Node *node)
{
    struct Node *current = node;
    while (current && current->right)
        current = current->right;
    return current;
}

/* ===================== ВЫСОТЫ И БАЛАНС ===================== */

int get_height(struct Node *N)
{
    return (N == NULL) ? 0 : N->height;
}

void update_height(struct Node *N)
{
    if (N)
    {
        int lh = get_height(N->left);
        int rh = get_height(N->right);
        N->height = (lh > rh ? lh : rh) + 1;
    }
}

int get_balance(struct Node *N)
{
    return (N == NULL) ? 0 : get_height(N->right) - get_height(N->left);
}

/* ===================== SWAP (НЕ ИСПОЛЬЗУЕТСЯ, НО ОСТАВЛЕН) ===================== */

void swap_nodes(struct Node *a, struct Node *b)
{
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

/* ===================== AVL ПОВОРОТЫ ===================== */

void right_rotate(struct Node **root)
{
    struct Node *y = *root;
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    *root = x;
}

void left_rotate(struct Node **root)
{
    struct Node *x = *root;
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    *root = y;
}

/* ===================== СОСТАВНЫЕ ПОВОРОТЫ (ОСТАВЛЕНЫ) ===================== */

void right_left_rotate(struct Node **root)
{
    right_rotate(&((*root)->right));
    left_rotate(root);
}

void left_right_rotate(struct Node **root)
{
    left_rotate(&((*root)->left));
    right_rotate(root);
}

/* ===================== БАЛАНСИРОВКА ===================== */

void balance_tree(struct Node **root)
{
    if (*root == NULL)
        return;

    int balance = get_balance(*root);

    /* Left heavy */
    if (balance < -1)
    {
        if (get_balance((*root)->left) > 0)
            left_rotate(&((*root)->left));   /* LR */

        right_rotate(root);                  /* LL */
    }
    /* Right heavy */
    else if (balance > 1)
    {
        if (get_balance((*root)->right) < 0)
            right_rotate(&((*root)->right)); /* RL */

        left_rotate(root);                   /* RR */
    }
}

/* ===================== СОЗДАНИЕ УЗЛА ===================== */

struct Node *create_node(char *name, long population,
                          char *phoneCode, double gdp,
                          long area, int key)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    if (!new_node)
        return NULL;

    strncpy(new_node->name, name, 99);
    new_node->name[99] = '\0';

    strncpy(new_node->phoneCode, phoneCode, 9);
    new_node->phoneCode[9] = '\0';

    new_node->population = population;
    new_node->gdp = gdp;
    new_node->area = area;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

/* ===================== ВСТАВКА ===================== */

struct Node *insert_node(struct Node *node, char *name,
                          long population, char *phoneCode,
                          double gdp, long area, int key)
{
    if (node == NULL)
        return create_node(name, population, phoneCode, gdp, area, key);

    if (key < node->key)
        node->left = insert_node(node->left, name, population, phoneCode, gdp, area, key);
    else if (key > node->key)
        node->right = insert_node(node->right, name, population, phoneCode, gdp, area, key);
    else
        return node;

    update_height(node);
    balance_tree(&node);

    return node;
}

/* ===================== КОПИРОВАНИЕ ДАННЫХ ===================== */

struct Node *copy_values(struct Node *dest, struct Node *src)
{
    if (!dest || !src)
        return dest;

    strncpy(dest->name, src->name, 99);
    dest->name[99] = '\0';

    strncpy(dest->phoneCode, src->phoneCode, 9);
    dest->phoneCode[9] = '\0';

    dest->population = src->population;
    dest->gdp = src->gdp;
    dest->area = src->area;
    dest->key = src->key;

    return dest;
}

/* ===================== УДАЛЕНИЕ ===================== */

struct Node *delete_node(struct Node *root, int key)
{
    if (root == NULL)
        return NULL;

    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else
    {
        /* 0 или 1 ребёнок */
        if (root->left == NULL || root->right == NULL)
        {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                free(root);
                return NULL;
            }
            else
            {
                struct Node *old = root;
                root = temp;
                free(old);
            }
        }
        /* 2 ребёнка */
        else
        {
            struct Node *temp = find_min(root->right);
            copy_values(root, temp);
            root->right = delete_node(root->right, temp->key);
        }
    }

    update_height(root);
    balance_tree(&root);

    return root;
}

/* ===================== ОБХОДЫ ===================== */

void inorder_traverse(struct Node *node)
{
    if (!node)
        return;

    inorder_traverse(node->left);
    printf("Country: %s, Population: %ld, Phone: %s, GDP: %.2f, Area: %ld, Key: %d\n",
           node->name, node->population, node->phoneCode,
           node->gdp, node->area, node->key);
    inorder_traverse(node->right);
}

void reverse_inorder_traverse(struct Node *node)
{
    if (!node)
        return;

    reverse_inorder_traverse(node->right);
    printf("Country: %s, Population: %ld, Phone: %s, GDP: %.2f, Area: %ld, Key: %d\n",
           node->name, node->population, node->phoneCode,
           node->gdp, node->area, node->key);
    reverse_inorder_traverse(node->left);
}

/* ===================== ОСВОБОЖДЕНИЕ ===================== */

void free_tree(struct Node *node)
{
    if (!node)
        return;

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

/* ===================== ТЕСТ ===================== */

void test_tree()
{
    struct Node *root = NULL;

    root = insert_node(root, "CountryA", 1000000, "+1", 15000.0, 1000000, 10);
    root = insert_node(root, "CountryB", 2000000, "+2", 20000.0, 2000000, 20);
    root = insert_node(root, "CountryC", 1500000, "+3", 18000.0, 1500000, 5);

    printf("Tree after adding:\n");
    inorder_traverse(root);

    root = delete_node(root, 10);

    printf("\nTree after deletion:\n");
    inorder_traverse(root);

    free_tree(root);
}

static void write_tree_inorder(FILE *fp, struct Node *node)
{
    if (!node)
        return;

    write_tree_inorder(fp, node->left);

    fprintf(fp, "%s,%ld,%s,%.2f,%ld,%d\n",
            node->name,
            node->population,
            node->phoneCode,
            node->gdp,
            node->area,
            node->key);
    write_tree_inorder(fp, node->right);
}

int write_tree_to_file(const char *filename, struct Node *root)
{
    if (!root)
        return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Error opening file for writing: %s\n", filename);
        perror("Reason");
        return -1;
    }

    /* Заголовок таблицы */
    fprintf(fp,
        "country_name,country_population,country_phoneCode,"
        "country_gdp,country_area,key\n");

    /* Запись данных дерева */
    write_tree_inorder(fp, root);

    fclose(fp);
    return 0;
}
