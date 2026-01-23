
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

