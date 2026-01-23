
#include "file_parsing.h"


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
    if (isalpha(c))
    {
        c = toupper(c);
        return c - 'A' + 1;
    }
    return 0;
}

unsigned long convert_in_key(const char *str)
{
    unsigned long key = 0;
    int max_letters = 6; // только первые 6 букв

    for (int i = 0; i < max_letters; i++)
    {
        int val = 0;
        if (str[i] != '\0') {
            val = letter_pos(str[i]);
        }
        key = key * 27 + val; // сдвигаем старшие разряды
    }

    return key;
}

int generate_key(CountryField mode_key, const struct CountryData *country)
{
    switch (mode_key)
    {
    case NAME:
        return convert_in_key(country->name); // Преобразование строки в целое число
    case POPULATION:
        return (int)(country->population % INT_MAX); // Приведение long к int с учетом переполнения
    case PHONE_CODE:
        return atoi(country->phoneCode); // Преобразование строки в целое число
    case GDP:
        return (int)((long)(country->gdp) % INT_MAX); // Приведение double к int с учетом переполнения
    case AREA:
        return (int)(country->area % INT_MAX); // Приведение long к int с учетом переполнения
    default:
        return 0; // Значение по умолчанию
    }
}


struct Node * read_file(const char *filename, CountryField mode_key)
{
    char buffer[256];
    struct Node *root = NULL;
    struct CountryData country;
    // check file opening
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file for reading: %s\n", filename);
        perror("Reason");
        fclose(fp);
        return NULL; // или обработка ошибки
    }
    // read file line by line
    while (fgets(buffer, 256, fp) != NULL)
    {
        country = parseCountryData(buffer);
        root = insert_node(root, country, generate_key(mode_key, &country));
    }
    if(root == NULL) {
        printf("No data loaded from file: %s\n", filename);
    } else {
        printf("Data successfully loaded from file: %s\n", filename);
    }
    fclose(fp);
    return root;
}

