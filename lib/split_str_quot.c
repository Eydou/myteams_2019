/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** str_to_quot
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functions.h>

List *is_fill_list(const char *start, const char *end, List *head)
{
    List *current = head;
    int check = 0;
    char *str = my_calloc((strlen(start) - strlen(end)) * sizeof(char *));
    int size = 0;

    for (int i = 0; start < end; i++) {
        str[i] = *start++;
    }
    if (str[0] == '"') {
        str++;
        str[strlen(str) - 1] = 0;
    }
    while (current->next != NULL) {
        current = current->next;
        check++;
    }
    current->str = strdup(str);
    current->next = malloc(sizeof(*head));
    current->next->next = NULL;
    return (head);
}

void is_t(const char *str, const char **start, int *state, List *list)
{
    if (*str == ' ') {
        list = is_fill_list(*start, str, list);
        *state = ' ';
    } else if (*str == '\"')
        *state = '\"';
}

void is_quot(const char *str, const char **start, int *state)
{
    if (*str == '\"') {
        *start = str;
        *state = '\"';
    } else if (*str != ' ') {
        *start = str;
        *state = 'T';
    }
}

char **setup_split_str_quot(char **tab, List *list, int *tab_size)
{
    List *current;
    (*tab_size) = 0;

    current = list;
    while (current->next != NULL) {
        current = current->next;
        (*tab_size)++;
    }
    tab = malloc(sizeof(char *) * *tab_size);
    for (int i = 0; i < *tab_size; i++) {
        tab[i] = strdup(list->str);
        list = list->next;
    }
    return tab;
}

char **split_str_quot(const char *str, char **tab, int *tab_size)
{
    List *list = malloc(sizeof(*list));
    list->next = NULL;
    const char *start;
    int state = ' ';
    for (; *str; str++) {
        switch (state) {
            case '\n':
            case ' ':
                is_quot(str, &start, &state);
                break;
            case 'T':
                is_t(str, &start, &state, list);
                break;
            case '\"':
                *str == '\"' ? state = 'T' : 0;
                break;
        }
    }
    (state != ' ') ? list = is_fill_list(start, str, list) : 0;
    return setup_split_str_quot(tab, list, tab_size);
}