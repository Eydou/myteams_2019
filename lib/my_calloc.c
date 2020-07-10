/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_calloc
*/

#include "functions.h"
#include <stdlib.h>

char *my_calloc(int size)
{
    char *res = malloc(size);

    if (res == NULL)
        return (NULL);
    for (int i = 0; i != size; i++)
        res[i] = '\0';
    return (res);
}
