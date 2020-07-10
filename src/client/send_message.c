/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_message
*/

#include "client.h"
#include "logging_client.h"
#include "functions.h"

void logout_client(s_client_t *client, char *message)
{
    if (!strcmp(message, "/logout")) {
        if (client->login != false)
            client_event_loggedout(client->uuid, client->user_name);
        close(client->sokfd);
        free(client);
        exit(0);
    }
}

void send_client(s_client_t *client, char *message)
{
    int len = 0;
    char **command = split_str_quot(message, command, &len);

    logout_client(client, message);
    if (!strcmp(message, ""))
        return;
    if ((client->login == false && strcmp(message, "/help") != 0) &&
    (client->login == false && strcmp(command[0], "/login") != 0)
    || !strcmp(message, "/login"))
        client_error_unauthorized();
    else if (!strcmp(command[0], "/login") && client->login == true) {
        client_error_already_exist();
        return;
    }
    if (!strcmp(message, "/help") && client->login == false)
        printf("USAGE:\n\t/help display help\n\
        /login [\"username\"] log with user\n\t/logout disconnect\n");
    else
        dprintf(client->sokfd, "%s\r\n", message);
    free_array(command, len);
}