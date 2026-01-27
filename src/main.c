#include <stdio.h>
#include "main.h"

enum commands
{
    CMD_HELP = 0,
    CMD_LOAD = 1,
    CMD_SAVE,
    CMD_DISPLAY,
    CMD_ADD_COUNTRY,
    CMD_DELETE,
    CMD_SEARCH,
    CMD_EXIT,
    CMD_SAVE_FILE_DEFAULT,
    CMD_LOAD_READY
};

CountryField convert(const char *sort_val)
{
    if (strcmp(sort_val, "NAME") == 0)
    {
        return NAME;
    }
    else if (strcmp(sort_val, "POPULATION") == 0)
    {
        return POPULATION;
    }
    else if (strcmp(sort_val, "PHONE_CODE") == 0)
    {
        return PHONE_CODE;
    }
    else if (strcmp(sort_val, "GDP") == 0)
    {
        return GDP;
    }
    else if (strcmp(sort_val, "AREA") == 0)
    {
        return AREA;
    }
    else
    {
        printf("Unknown sort value. Defaulting to NAME.\n");
        return NAME; // Значение по умолчанию
    }
    return NAME; // Значение по умолчанию
}

void command_interface(enum commands cmd, struct Node **root, int *size)
{
    // Реализация командного интерфейса
    int width_begin = 10;
    int width_end = 15;
    static char name_file_in[100];
    char name_file_out[100];
    char buff[100];
    char sort_val[100] = "NAME";
    static CountryField sort_value_general = NAME;
    CountryField search_val = NAME;
    struct Node *sort_root;
    struct CountryData country;
    int tmp;
    {
        /* data */
    };

    switch (cmd)
    {
    case CMD_HELP:
        printf("%*s\n", width_begin, "Available commands:");
        printf("%*d - Help\n", width_end, CMD_HELP);
        printf("%*d - Load data from file\n", width_end, CMD_LOAD);
        printf("%*d - Save data to file\n", width_end, CMD_SAVE);
        printf("%*d - Display data\n", width_end, CMD_DISPLAY);
        printf("%*d - Add new record\n", width_end, CMD_ADD_COUNTRY);
        printf("%*d - Delete record\n", width_end, CMD_DELETE);
        printf("%*d - Search record\n", width_end, CMD_SEARCH);
        printf("%*d - Exit program\n", width_end, CMD_EXIT);
        printf("%*d - Save ready data from default file\n", width_end, CMD_SAVE_FILE_DEFAULT);
        printf("%*d - Load ready data from default file\n", width_end, CMD_LOAD_READY);
        break;
    case CMD_LOAD:
        printf("%*s\n", width_begin, "Write name of file without .txt: ");
        scanf("%s", name_file_in); // ввод строки без пробелов
        sprintf(name_file_in, "%s.txt", name_file_in);
        printf("%*s\n", width_begin, "Write sort value: ");
        printf("%*s\n", width_begin, "Available sort values: NAME, POPULATION, PHONE_CODE, GDP, AREA");
        scanf("%s", sort_val); // ввод строки без пробелов
        sort_value_general = convert(sort_val);
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
    case CMD_ADD_COUNTRY:
        // Добавление новой записи
        printf("Write name:\n");
        scanf("%99s", country.name);

        printf("Write population:\n");
        scanf("%ld", &country.population);

        printf("Write phone code:\n");
        scanf("%9s", country.phoneCode);

        printf("Write GDP:\n");
        scanf("%lf", &country.gdp);

        printf("Write area:\n");
        *size += 1;
        scanf("%ld", &country.area);
        insert_node(*root, country, generate_key(sort_value_general, &country));
        print_node_co_data(search_node(*root, generate_key(sort_value_general, &country)));
        break;
    case CMD_LOAD_READY:
        // Добавление новой записи
        sprintf(name_file_in, "data/countries.txt");
        *root = read_file(name_file_in, convert(sort_val));
        sort_value_general = convert(sort_val);
        *size = read_amount(name_file_in);
        // Загрузка данных из файла
        break;
    case CMD_SAVE_FILE_DEFAULT:
        printf("%*s\n", width_begin, "Write to file ");
        sprintf(name_file_out, "data/c.txt");
        write_file(name_file_out, size, *root);
        break;
    case CMD_DELETE:
        // Удаление записи
        printf("%*s\n", width_begin, "Write delete parameter:");
        printf("%*s\n", width_begin, "Available sort values: NAME - 0, POPULATION - 1, PHONE_CODE - 2, GDP - 3, AREA - 4");
        scanf("%d", &tmp);
        search_val = (CountryField)tmp;
        switch (search_val)
        {
        case NAME:
            printf("%*s\n", width_begin, "Write name:");
            scanf("%99s", country.name);
            break;
        case POPULATION:
            printf("%*s\n", width_begin, "Write population:");
            scanf("%ld", &country.population);
            break;
        case PHONE_CODE:
            printf("%*s\n", width_begin, "Write phone_code:");
            scanf("%9s", country.phoneCode);
            break;
        case GDP:
            printf("%*s\n", width_begin, "Write GDP:");
            scanf("%lf", &country.gdp);
            break;
        case AREA:
            printf("%*s\n", width_begin, "Write area:");
            scanf("%ld", &country.area);
            break;
        default:
            printf("%*s\n", width_begin, "No parameter!!!");
            break;
        }
        *root = read_file(name_file_in, search_val);
        delete_node(*root, generate_key(search_val, &country));
        printf("%*s\n", width_begin, "Node delete!!!");
        print_node_co_data(search_node(sort_root, generate_key(search_val, &country)));
        *root = read_file(name_file_in, sort_value_general);
        break;
    case CMD_SEARCH:
        printf("%*s\n", width_begin, "Write search parameter:");
        printf("%*s\n", width_begin, "Available sort values: NAME - 0, POPULATION - 1, PHONE_CODE - 2, GDP - 3, AREA - 4");
        scanf("%d", &tmp);
        search_val = (CountryField)tmp;
        switch (search_val)
        {
        case NAME:
            printf("%*s\n", width_begin, "Write name:");
            scanf("%99s", country.name);
            break;
        case POPULATION:
            printf("%*s\n", width_begin, "Write population:");
            scanf("%ld", &country.population);
            break;
        case PHONE_CODE:
            printf("%*s\n", width_begin, "Write phone_code:");
            scanf("%9s", country.phoneCode);
            break;
        case GDP:
            printf("%*s\n", width_begin, "Write GDP:");
            scanf("%lf", &country.gdp);
            break;
        case AREA:
            printf("%*s\n", width_begin, "Write area:");
            scanf("%ld", &country.area);
            break;
        default:
            printf("%*s\n", width_begin, "No parameter!!!");
            break;
        }
        sort_root = read_file(name_file_in, search_val);
        print_node_co_data(search_node(sort_root, generate_key(search_val, &country)));
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
    while (1)
    {
        if (start_flag)
        {
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
