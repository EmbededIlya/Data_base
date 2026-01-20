
#include <tree.h>





struct Node *create_node(struct CountryData new_country, int key)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    if (!new_node)
        return NULL;
    new_node->country = new_country;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}




/* ===================== ПОИСК МИНИМУМА / МАКСИМУМА ===================== */

struct Node *find_min(struct Node *node)
{
    
}

struct Node *find_max(struct Node *node)
{
    
}

/* ===================== ВЫСОТЫ И БАЛАНС ===================== */

int get_height(struct Node *N)
{
   
}

void update_height(struct Node *N)
{
   
}

int get_balance(struct Node *N)
{
    
}

/* ===================== SWAP (НЕ ИСПОЛЬЗУЕТСЯ, НО ОСТАВЛЕН) ===================== */

void swap_nodes(struct Node *a, struct Node *b)
{
    
}

/* ===================== AVL ПОВОРОТЫ ===================== */

void right_rotate(struct Node **root)
{
    
}

void left_rotate(struct Node **root)
{
   
}

/* ===================== СОСТАВНЫЕ ПОВОРОТЫ (ОСТАВЛЕНЫ) ===================== */

void right_left_rotate(struct Node **root)
{
    
}

void left_right_rotate(struct Node **root)
{
    
}

/* ===================== БАЛАНСИРОВКА ===================== */

void balance_tree(struct Node **root)
{
    
}




struct Node *search_node(struct Node *root, int key)
{
    if(root == NULL)
        return NULL;
    if(key == root->key)
        return root;
    else if(key < root->key)
        return search_node(root->left, key);
    else
        return search_node(root->right, key);
}


{
    if (root == NULL)
        return NULL;

    int cmp = strcmp(name, root->name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return search_node_by_name(root->left, name);
    else
        return search_node_by_name(root->right, name);
}
/* ===================== ВСТАВКА ===================== */

struct Node *insert_node(struct Node *root, char *name,
                          long population, char *phoneCode,
                          double gdp, long area, int key)
{
    if(key < root->key){
        if(root->left == NULL)
            root->left = create_node(name, population, phoneCode, gdp, area, key);
        else
            root->left = insert_node(root->left, name, population, phoneCode, gdp, area, key);
    } else if(key > root->key){
        if(root->right == NULL)
            root->right = create_node(name, population, phoneCode, gdp, area, key);
        else
            root->right = insert_node(root->right, name, population, phoneCode, gdp, area, key);
    }
    return root;
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
