/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_list_client
*/

#include "client.h"
#include "functions.h"
#include "logging_client.h"

void is_list(char *message, char **command, s_client_t *client,
int len)
{
    if (!strcmp(command[1], "team"))
        for (int i = 2; i != len;) {
            client_print_team(command[i + 1], command[i], command[i + 2]);
            i = i + 3;
        }
}