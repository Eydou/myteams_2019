/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_use_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

void is_info(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 1) {
        dprintf(client[id].sockfd, "invalid command");
        return;
    }
    if (client[id].use == 0)
        send_commands_users(client, id);
}