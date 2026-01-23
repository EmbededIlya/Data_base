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
int convert_in_key(char *str);

/* Get country name from a line */
char *get_country_name(const char *line);

/* Create tree from file */
struct Node *create_tree_file(const char *filename, CountryField mode_key);

/* Write tree to file */
int write_tree_to_file(const char *filename, struct Node *root);

#endif // FILE_WORK_H
