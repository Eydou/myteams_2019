/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_client
*/

#include "client.h"
#include "functions.h"
#include "logging_client.h"

static command _command[13] = {&is_users, &is_log, &is_close, &is_user,
&is_error, &is_message_private, &is_display_message, &is_create_team,
&is_subscribe, &is_unsubscribe, &is_list, &is_subed, &is_create_channel};

void is_log(char *message, char **command, s_client_t *client, int len)
{
    client_event_loggedin(command[2], command[1]);
}

void is_users(char *message, char **command, s_client_t *client, int len)
{
    int status = 0;

    for (int i = 1; i != len;) {
        status = atoi(command[i + 2]);
        if (status > 1)
            status = 1;
        client_print_users(command[i + 1], command[i], status);
        i = i + 3;
    }
}

static void is_login(char *message, s_client_t *client)
{
    char *command = strtok(message, ";");
    char *username = NULL;
    char *uuid = NULL;
    command = strtok(NULL, ";");
    username = strdup(command);
    command = strtok(NULL, ";");
    uuid = strdup(command);
    client_event_loggedin(uuid, username);
    client->login = true;
    client->uuid = uuid;
    client->user_name = username;
}

void command_management(char *message, s_client_t *client)
{
    int len = 0;
    char **command = split_str_client(message, command, &len);
    char *command_first[] = {"users", "log", "close", "user", "error",
    "message", "display_message", "create_team", "sub", "unsub", "list",
    "subed", "create_channel"};

    if (!strcmp(command[0], "login") && client->login == false) {
        is_login(message, client);
        return;
    }
    if (client->login == true) {
        for (int i = 0; i != 13; i++) {
            if (!strcmp(command[0], command_first[i])) {
                _command[i](message, command, client, len);
                return;
            }
        }
    }
    printf("%s\n", message);
    free_array(command, len);
}