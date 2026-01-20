#include "main.h"


static void calc_widths(struct Node *node, struct TableWidth *w)
{
    if (!node)
        return;

    calc_widths(node->left, w);

    char buf[64];

    if (strlen(node->name) > w->name)
        w->name = strlen(node->name);

    sprintf(buf, "%ld", node->population);
    if (strlen(buf) > w->population)
        w->population = strlen(buf);

    if (strlen(node->phoneCode) > w->phone)
        w->phone = strlen(node->phoneCode);

    sprintf(buf, "%.2f", node->gdp);
    if (strlen(buf) > w->gdp)
        w->gdp = strlen(buf);

    sprintf(buf, "%ld", node->area);
    if (strlen(buf) > w->area)
        w->area = strlen(buf);

    sprintf(buf, "%d", node->key);
    if (strlen(buf) > w->key)
        w->key = strlen(buf);

    calc_widths(node->right, w);
}


static void print_line(FILE *fp, struct TableWidth *w)
{
    fprintf(fp, "+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+\n",
        (int)w->name,       "----------------------------------------",
        (int)w->population, "----------------------------------------",
        (int)w->phone,      "----------------------------------------",
        (int)w->gdp,        "----------------------------------------",
        (int)w->area,       "----------------------------------------",
        (int)w->key,        "----------------------------------------");
}

static void print_header(FILE *fp, struct TableWidth *w)
{
    print_line(fp, w);

    fprintf(fp,
        "| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
        (int)w->name, "Country",
        (int)w->population, "Population",
        (int)w->phone, "Phone",
        (int)w->gdp, "GDP",
        (int)w->area, "Area",
        (int)w->key, "Key");

    print_line(fp, w);
}

static void print_rows(FILE *fp, struct Node *node, struct TableWidth *w)
{
    if (!node)
        return;

    print_rows(fp, node->left, w);

    fprintf(fp,
        "| %-*s | %*ld | %-*s | %*.2f | %*ld | %*d |\n",
        (int)w->name, node->name,
        (int)w->population, node->population,
        (int)w->phone, node->phoneCode,
        (int)w->gdp, node->gdp,
        (int)w->area, node->area,
        (int)w->key, node->key);

    print_rows(fp, node->right, w);
}

int write_tree_pretty(const char *filename, struct Node *root)
{
    if (!root)
        return -1;

    struct TableWidth w = {
        .name = strlen("Country"),
        .population = strlen("Population"),
        .phone = strlen("Phone"),
        .gdp = strlen("GDP"),
        .area = strlen("Area"),
        .key = strlen("Key")
    };

    calc_widths(root, &w);

    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        perror("Error opening file");
        return -1;
    }

    print_header(fp, &w);
    print_rows(fp, root, &w);
    print_line(fp, &w);

    fclose(fp);
    return 0;
}
