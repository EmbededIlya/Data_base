#include "main.h"


// ---------- вспомогательный ввод ----------
void input_string(int y, int x, char *buf, int size) {
    mvprintw(y, x, "> ");
    echo();
    getnstr(buf, size - 1);
    noecho();
}

// ---------- экраны ----------
void load_menu(struct Node **root) {
    char filename[128];
    clear(); box(stdscr,0,0);
    mvprintw(1,2,"Load data from file");
    input_string(3,2,filename,sizeof(filename));
    // *root = load_from_file(filename);
    mvprintw(5,2,"Loaded. Press any key...");
    getch();
}

void save_menu(struct Node *root) {
    char filename[128];
    clear(); box(stdscr,0,0);
    mvprintw(1,2,"Save data to file");
    input_string(3,2,filename,sizeof(filename));
    // save_to_file(root, filename);
    mvprintw(5,2,"Saved. Press any key...");
    getch();
}

void add_menu(struct Node **root) {
    char name[64], phone[16];
    int key;
    long population, area;
    double gdp;

    clear(); box(stdscr,0,0);
    mvprintw(1,2,"Add element");

    mvprintw(3,2,"Key");          scanw("%d",&key);
    mvprintw(4,2,"Name");         scanw("%63s",name);
    mvprintw(5,2,"Population");   scanw("%ld",&population);
    mvprintw(6,2,"Phone code");   scanw("%15s",phone);
    mvprintw(7,2,"GDP");          scanw("%lf",&gdp);
    mvprintw(8,2,"Area");         scanw("%ld",&area);

    *root = insert_node(*root, name, population, phone, gdp, area, key);

    mvprintw(10,2,"Added. Press any key...");
    getch();
}

void delete_menu(struct Node **root) {
    int key;
    clear(); box(stdscr,0,0);
    mvprintw(1,2,"Delete element");
    mvprintw(3,2,"Key"); scanw("%d",&key);
    *root = delete_node(*root, key);
    mvprintw(5,2,"Deleted. Press any key...");
    getch();
}
