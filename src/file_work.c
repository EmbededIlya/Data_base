
#include "file_work.h"

typedef unsigned char byte;

// Функция для парсинга строки и заполнения структуры
struct CountryData parseCountryData(const char *line)
{
    struct CountryData country;
    memset(&country, 0, sizeof(country));

    sscanf(line, "%99[^\t]\t%ld\t%9[^\t]\t%lf\t%ld",
           country.name,
           &country.population,
           country.phoneCode,
           &country.gdp,
           &country.area);

    return country;
}

// Функция для вывода данных страны
void printCountryData(const struct CountryData *country)
{
    printf("Country: %s\n", country->name);
    printf("Population: %ld\n", country->population);
    printf("Phone code: %s\n", country->phoneCode);
    printf("GDP: %.1f\n", country->gdp);
    printf("Area: %ld sq.km\n\n", country->area);
}

int read_amount(const char *filename)
{
    // буфер для считавания данных из файла
    char buffer[64];
    // чтение из файла
    int amount = 0;
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file for reading: %s\n", filename);
        perror("Reason");
        fclose(fp);
        return 1; // или обработка ошибки
    }

    // пока не дойдем до конца, считываем по 256 байт из файла f1
    while ((fgets(buffer, 64, fp)) != NULL)
    {
        amount++;
        printf("Amount = %d\n", amount); // Добавил \n для удобства чтения
    }
    fclose(fp);
    return amount;
}

int letter_pos(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 1;
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 1;
    return 0;
}

int convert_in_key(char *str)
{
    int key = 0;
    int weights[] = {10000, 1000, 100, 10, 1};
    for (int i = 0; i < 5; i++)
    {
        key += letter_pos(str[i]) * weights[i];
    }
    return key;
}

char *get_country_name(const char *line)
{
    static char country[256]; // Статический буфер для результата

    if (line == NULL)
    {
        return NULL;
    }

    const char *start = NULL;
    const char *end = NULL;
    const char *p = line;

    // Находим первую табуляцию (после номера)
    while (*p != '\0' && *p != '\t')
    {
        p++;
    }

    if (*p == '\t')
    {
        start = p + 1; // Начало названия страны

        // Ищем следующую табуляцию (конец названия страны)
        p = start;
        while (*p != '\0' && *p != '\t')
        {
            p++;
        }

        if (*p == '\t')
        {
            end = p; // Конец названия страны

            // Копируем название страны в статический буфер
            size_t country_len = end - start;

            // Проверяем, не превышает ли длина размер буфера
            if (country_len >= sizeof(country))
            {
                country_len = sizeof(country) - 1; // Оставляем место для '\0'
            }

            strncpy(country, start, country_len);
            country[country_len] = '\0';
            return country;
        }
    }

    return NULL; // Не удалось найти название страны
}

struct Node *create_tree_file(const char *filename)
{
    // Реализация функции создания дерева из файла
    char buffer[512];
    struct CountryData country;
    struct Node *root = NULL;
    int count = 0;
    int line_num = 0;

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file for reading: %s\n", filename);
        perror("Reason");
        return NULL;
    }

    // Читаем строку за строкой из файла
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {   
        printf("Read:\n");
        line_num++;

        // Пропускаем пустые строки и строки с только пробельными символами
        char *p = buffer;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p == '\n' || *p == '\r' || *p == '\0')
            continue;

        country = parseCountryData(p);

        // Проверяем, что страна имеет имя
        if (strlen(country.name) > 0)
        {
            int key = convert_in_key(country.name);
            root = insert_node(root, country.name, country.population, country.phoneCode, country.gdp, country.area, key);
            count++;
        }
    }

    fclose(fp);
    return root;
}

