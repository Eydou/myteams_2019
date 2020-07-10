/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** functions
*/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdbool.h>

bool is_number(char *str);
void perror_84(const char *str);
char *get_next_line(const int fd);
char **split_str_quot(const char *str, char **tab, int *);
char **split_str_client(const char *str, char **tab, int *);
void free_array(char **array, int len);
char *my_calloc(int size);
char *itoa(int nb);

typedef struct List List;
struct List {
    char *str;
    List *next;
};

#endif /* !FUNCTIONS_H_ */
