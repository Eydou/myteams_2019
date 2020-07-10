/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

void is_users(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 1)
        dprintf(client[id].sockfd, "Please enter a valid command");
    else
        send_commands_users(client, id);
}

void is_user(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 2)
        dprintf(client[id].sockfd, "Please enter a valid command");
    else
        search_user(client, id);
}

void is_send(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 3)
        dprintf(client[id].sockfd, "Please enter a valid command");
    else
        send_message_user(client, id);
}

void is_messages(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 2)
        dprintf(client[id].sockfd, "Please enter a valid command");
    else
        display_message_user(client, id);
}