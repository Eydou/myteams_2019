/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_management
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

#include <errno.h>

int check_client(client_serv_t client[MAX_CLIENT], int id)
{
    client[id].message = NULL;
    client[id].message = get_next_line(client[id].sockfd);

    if (client[id].message == NULL) {
        if (client[id].login == true) {
            server_event_user_logged_out(client[id].uuid);
            share_close_client(client, id);
            status_client(client, id, 0);
            clean_client(client, id);
            return -1;
        } else {
            clean_client(client, id);
            return -1;
        }
    }
    return 0;
}

void start_client(client_serv_t client[MAX_CLIENT], int id)
{
    int i = 0;
    char **command = NULL;
    client[id].message[strlen(client[id].message) - 1] = '\0';
    client[id].command = split_str_quot(client[id].message,
    command, &i);
    if (!strcmp(client[id].message, "/help")) {
        help_command(client, id);
        return;
    }
    handling_command_client(client, id, i);
    free(client[id].message);
    free_array(client[id].command, i);
}

void fill_client(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv)
{
    int new_socket = 0;
    struct sockaddr_in client = {0};
    int client_size = sizeof(client);

    if (FD_ISSET(serv->sockfd, &serv->readfds)) {
        if ((new_socket = accept(serv->sockfd,
        (struct sockaddr *)&client, (socklen_t *)&client_size)) == -1) {
            perror_84("accept()");
        }
        for (int i = 0; i < MAX_CLIENT; i++) {
            s_client[i].ip = client.sin_addr.s_addr;
            s_client[i].address = client;
            s_client[i].len_addr = sizeof(client);
            if (s_client[i].sockfd == 0) {
                s_client[i].sockfd = new_socket;
                break;
            }
        }
    }
}

int init_client(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv)
{
    FD_ZERO(&serv->readfds);
    FD_SET(serv->sockfd, &serv->readfds);
    serv->max_sd = serv->sockfd;
    for (int i = 0 ; i < MAX_CLIENT ; i++) {
        if (s_client[i].sockfd > 0)
            FD_SET(s_client[i].sockfd, &serv->readfds);
        if (s_client[i].sockfd > serv->max_sd)
            serv->max_sd = s_client[i].sockfd;
    }
    if (select(serv->max_sd + 1 , &serv->readfds , NULL , NULL , NULL) == -1) {
        if (errno == EINTR)
            return -1;
        else
            perror_84("select()");
    }
    return 0;
}