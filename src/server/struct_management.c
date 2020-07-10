/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** struct
*/

#include "server.h"

void init_struct_client(client_serv_t client[MAX_CLIENT], int id)
{
    client[id].login = false;
    client[id].uuid = NULL;
    client[id].message = NULL;
    client[id].use = 0;
}

s_serv_t *init_server(int sockfd, int max_sd, fd_set fds, s_serv_t *serv)
{
    serv = malloc(sizeof(s_serv_t));
    serv->fds = fds;
    serv->max_sd = max_sd;
    serv->sockfd = sockfd;

    return serv;
}

void close_server(client_serv_t client[MAX_CLIENT],
s_serv_t *serv)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (FD_ISSET(client[i].sockfd, &serv->readfds))
            clean_client(client, i);
    }
    close(serv->sockfd);
    close_status_client();
}