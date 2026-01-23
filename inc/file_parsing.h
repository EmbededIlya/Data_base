#ifndef FILE_WORK_H
#define FILE_WORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tree.h"

typedef enum
{
    NAME,
    POPULATION,
    PHONE_CODE,
    GDP,
    AREA
} CountryField;

/* Parse a line and extract country data */
struct CountryData parseCountryData(const char *line);

/* Print country data to console */
void printCountryData(const struct CountryData *country);

/* Read the amount of lines from a file */
int read_amount(const char *filename_r);

/* Get letter position (A=1, B=2, etc.) */
int letter_pos(char c);

/* Convert country name to key */
unsigned long convert_in_key(const char *str);

/* Get country name from a line */
char *get_country_name(const char *line);

/* Read file and populate tree */
struct Node *read_file(const char *filename, CountryField mode_key);

/* Generate key based on country data and selected field */
int generate_key(CountryField mode_key, const struct CountryData *country);  
/* Write tree data to file */
int write_file(const char *filename, int*size, struct Node *root);  

#endif // FILE_WORK_H
