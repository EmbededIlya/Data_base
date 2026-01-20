#ifndef INTERFACE_H
#define INTERFACE_H

#include <curses.h>

// предварительное объявление структуры
struct Node;

/* ---------- вспомогательный ввод ---------- */
void input_string(int y, int x, char *buf, int size);

/* ---------- экраны (меню) ---------- */
void load_menu(struct Node **root);
void save_menu(struct Node *root);
void add_menu(struct Node **root);
void delete_menu(struct Node **root);

#endif // INTERFACE_H
