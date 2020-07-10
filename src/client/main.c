/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include "client.h"
#include "functions.h"

static size_t help(int quit)
{
    printf("USAGE: ./myteams_cli ip port\n\n  \
    ip   is the server ip address on which the server socket listens.\n  \
    port is the port number on which the server socket listens\n");

    return quit;
}

int main(int ac, char **av)
{
    if (ac == 3) {
        if (ac == 2 && !strcmp(av[1], "-help"))
            return help(0);
        if (is_number(av[2]) == true ) {
            return start_client(av[1], atoi(av[2]));
        } else {
            printf("invalid port\n");
            return 84;
        }
    }
    return help(84);
}