/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_client
*/

#include "client.h"
#include "functions.h"
#include "logging_client.h"

void is_close(char *message, char **command, s_client_t *client, int len)
{
    client_event_loggedout(command[2], command[1]);
}

void is_user(char *message, char **command, s_client_t *client, int len)
{
    int status = 0;

    status = atoi(command[3]);
        if (status > 1)
            status = 1;
    client_print_user(command[2], command[1], status);
}

void is_message_private(char *message, char **command, s_client_t *client,
int len)
{
    client_event_private_message_received(command[1], command[2]);
}

void is_error(char *message, char **command, s_client_t *client, int len)
{
    if (!strcmp(command[1], "user"))
        client_error_unknown_user(command[2]);
    else if ((!strcmp(command[1], "unauthoriz")))
        client_error_unauthorized();
    else if (!strcmp(command[1], "exist"))
        client_error_already_exist();
    else if (!strcmp(command[1], "team"))
        client_error_unknown_team(command[2]);
}