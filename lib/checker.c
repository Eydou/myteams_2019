/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** checker
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *itoa(int nb)
{
    int count = 1;
    int n = nb;
    char *str = NULL;
    for (;n > 10; count++)
        n = n / 10;
    str = malloc(count+1);
    str[count] = '\0';
    n = nb;
    for (int i = count - 1; i >= 0; i--) {
        str[i] = (n % 10) + '0';
        n = n / 10;
    }
    return str;
}

bool is_number(char *str)
{
    bool is_correct = true;
    size_t length = strlen(str);

    for (int i = 0; i < length; i++) {
        if (!isdigit(str[i])) {
            is_correct = false;
        }
    }
    return is_correct;
}

void free_array(char **array, int len)
{
    int row = 0;

    for (int row = 0; row != len; row++);
    for (row -= 1; row >= 0; row--)
        free(array[row]);
    free(array);
}

void perror_84(const char *str)
{
    perror(str);
    exit(84);
}