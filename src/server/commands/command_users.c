/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_users
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static command _command[11] = {&is_users, &is_user, &is_send, &is_messages,
&is_create, &is_sub, &is_unsub, &is_use, &is_info, &is_list, &is_subed};

static void command_management(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    char *command_first[] = {"/users", "/user", "/send", "/messages",
    "/create", "/subscribe", "/unsubscribe", "/use", "/info", "/list",
    "/subscribed"};

    for (int i = 0; i != 11; i++) {
        if (!strcmp(client[id].command[0], command_first[i])) {
            _command[i](client, id, len);
            return;
        }
    }
}

void handling_command_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len == 1) {
        if (client[id].login == false
        && !strcmp(client[id].message, "/logout")) {
            clean_client(client, id);
            return;
        }
    } else if (len == 2) {
        if (!strcmp(client[id].command[0], "/login")) {
            login_client(client, id, len);
            return;
        }
    }
    if (client[id].login == true) {
        command_management(client, id, len);
    }
}

void help_command(client_serv_t client[MAX_CLIENT], int id)
{
    c_message(client[id].sockfd,
    "HELP :\n\t/login [”username”] : login with your id\n");
}