
#include "file_work.h"

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

struct Node *create_tree_file(const char *filename, CountryField mode_key)
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
    int key = 0;
    // Читаем строку за строкой из файла
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
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
            if (mode_key == NAME)
            {
                key = convert_in_key(country.name);
            }
            else if (mode_key == POPULATION)
            {
                key = (int)(country.population / 1000000); // Пример: ключ - население в миллионах
            }
            else if (mode_key == GDP)
            {
                key = (int)(country.gdp); // Пример: ключ - ВВП
            }
            else if (mode_key == AREA)
            {
                key = (int)(country.area / 1000); // Пример: ключ - площадь в тысячах кв.км
            }
            root = insert_node(root, country.name, country.population, country.phoneCode, country.gdp, country.area, key);
            count++;
        }
    }

    fclose(fp);
    return root;
}
