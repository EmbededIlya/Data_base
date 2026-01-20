#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include "tree.h"

/* ===================== ШИРИНЫ КОЛОНОК ===================== */

struct TableWidth {
    size_t name;
    size_t population;
    size_t phone;
    size_t gdp;
    size_t area;
    size_t key;
};

/* ===================== ПУБЛИЧНЫЙ ИНТЕРФЕЙС ===================== */

/**
 * Записывает AVL-дерево в файл в виде красиво выровненной таблицы
 *
 * @param filename  имя файла для записи
 * @param root      корень AVL-дерева
 *
 * @return 0  — успех
 *        -1  — ошибка
 */
int write_tree_pretty(const char *filename, struct Node *root);

#endif /* TABLE_H */
