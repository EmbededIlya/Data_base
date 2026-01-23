#include <stdio.h>
#include "main.h"


enum commands {
    CMD_HELP = 0,
    CMD_LOAD = 1,
    CMD_SAVE,
    CMD_DISPLAY,
    CMD_ADD,
    CMD_DELETE,
    CMD_SEARCH,
    CMD_EXIT
};

CountryField convert(const char *sort_val) {
    if (strcmp(sort_val, "NAME") == 0) {
        return NAME;
    } else if (strcmp(sort_val, "POPULATION") == 0) {
        return POPULATION;
    } else if (strcmp(sort_val, "PHONE_CODE") == 0) {
        return PHONE_CODE;
    } else if (strcmp(sort_val, "GDP") == 0) {
        return GDP;
    } else if (strcmp(sort_val, "AREA") == 0) {
        return AREA;
    } else {
        printf("Unknown sort value. Defaulting to NAME.\n");
        return NAME; // Значение по умолчанию
    }
    return NAME; // Значение по умолчанию
}

void command_interface(enum commands cmd, struct Node **root, int *size) {
    // Реализация командного интерфейса
    int width_begin = 10;
    int width_end = 15;
    char name_file_in[100];
    char name_file_out[100];
    char sort_val[100];
    switch (cmd) {
        case CMD_HELP:
            printf("%*s\n", width_begin, "Available commands:");
            printf("%*d - Help\n", width_end, CMD_HELP);
            printf("%*d - Load data from file\n", width_end, CMD_LOAD);
            printf("%*d - Save data to file\n", width_end, CMD_SAVE);
            printf("%*d - Display data\n", width_end, CMD_DISPLAY);
            printf("%*d - Add new record\n", width_end, CMD_ADD);
            printf("%*d - Delete record\n", width_end, CMD_DELETE);
            printf("%*d - Search record\n", width_end, CMD_SEARCH);
            printf("%*d - Exit program\n", width_end, CMD_EXIT);
            break;
        case CMD_LOAD:
            printf("%*s\n", width_begin, "Write name of file without .txt: ");
            scanf("%s", name_file_in); // ввод строки без пробелов
            sprintf(name_file_in, "%s.txt", name_file_in);
            printf("%*s\n", width_begin, "Write sort value: ");
            printf ("%*s\n", width_begin, "Available sort values: NAME, POPULATION, PHONE_CODE, GDP, AREA");
            scanf("%s", sort_val); // ввод строки без пробелов
            *root = read_file(name_file_in, convert(sort_val));
            *size = read_amount(name_file_in);
            // Загрузка данных из файла
            break;
        case CMD_SAVE:
            printf("%*s\n", width_begin, "Write name of file that will save data without .txt: ");
            scanf("%s", name_file_out); // ввод строки без пробелов
            sprintf(name_file_out, "%s.txt", name_file_out);
            write_file(name_file_out, size, *root);
            // Сохранение данных в файл
            break;
        case CMD_DISPLAY:
            // Отображение данных
            inorder_traverse(*root);
            break;
        case CMD_ADD:
            // Добавление новой записи
            break;
        case CMD_DELETE:
            // Удаление записи
            break;
        case CMD_SEARCH:
            // Поиск записи
            break;
        case CMD_EXIT:
            // Выход из программы
            break;
        
        default:
            printf("Unknown command - try command help\n");
            break;
    }

}

int main()
{

    // printf("---------------------------------NEEEEEWWWW---------------------------:\n");
    // struct Node *root = create_tree_file("data/countries.txt", NAME);
    // inorder_traverse(root);
    // write_tree_pretty("data/countries.csv", root);
    // free_tree(root);
    // printf("---------------------------------END---------------------------:\n");
    bool start_flag = 1;
    bool exit_flag = 0;
    struct Node *root = NULL;
    int size_file = 0;
    while(1) {
        if(start_flag){
            printf("----------------------Start Menu------------------------\n");
            start_flag = false;
            command_interface(CMD_HELP, &root, &size_file);
        }
        printf("Enter command number: ");   
        int cmd;
        scanf("%d", &cmd);
        command_interface(cmd, &root, &size_file);
    }
    return 0;
}

