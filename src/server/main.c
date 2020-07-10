/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include "server.h"
#include "functions.h"

#include <stdbool.h>

static size_t help(int quit)
{
    printf("USAGE: ./myteams_server port\n\n  \
    port is the port number on which the server socket listens.\n");

    return quit;
}

size_t main(int ac, char **av)
{
    if (ac == 2) {
        if (!strcmp(av[1], "-help"))
            return help(0);
        if (is_number(av[1]) == true) {
            return start_server(atoi(av[1]));
        } else {
            printf("invalid port\n");
            return 84;
        }
    }
    return help(84);
}