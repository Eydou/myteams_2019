/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** close_client
*/


#include "server.h"
#include "functions.h"
#include "logging_server.h"

#include <errno.h>

void clean_client(client_serv_t client[MAX_CLIENT], int id)
{
    client[id].message = NULL;
    dprintf(client[id].sockfd, "end_client");
    close(client[id].sockfd);
    client[id].sockfd = 0;
    memset(&client[id].address, 0, sizeof client[id].address);
    client[id].login = false;
    client[id].uuid = NULL;
    client[id].user_name = NULL;
}

void share_close_client(client_serv_t client[MAX_CLIENT], int id)
{
    for (int i = 0; i != MAX_CLIENT; i++) {
        if (i != id) {
            if (client[i].login == true)
                dprintf(client[i].sockfd, "close;%s;%s", client[id].user_name,
                client[id].uuid);
        }
    }
}