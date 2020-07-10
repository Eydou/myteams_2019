/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** server
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"
#include <signal.h>

static void handle_signal_action(int sig_number)
{
    run = 0;
}

static int loop_server(client_serv_t s_client[MAX_CLIENT], s_serv_t *serv)
{
    is_save_file();
    signal(SIGINT, handle_signal_action);
    load_user_infile();
    for (int id = 0; id < MAX_CLIENT; id++) {
        init_struct_client(s_client, id);
    }
    for (;run != 0;) {
        if (init_client(s_client, serv) != 0)
            continue;
        fill_client(s_client, serv);
        for (int i = 0; i < MAX_CLIENT; i++) {
            if (FD_ISSET(s_client[i].sockfd, &serv->readfds)) {
                if (check_client(s_client, i) == 0)
                    start_client(s_client, i);
            }
        }
    }
    close_server(s_client, serv);
    return 0;
}

static int run_server(int sockfd, struct sockaddr_in s_addr, int port)
{
    client_serv_t s_client[MAX_CLIENT];
    fd_set fds;
    int max_sd = sockfd;
    s_serv_t *serv;

    for (int i = 0; i < MAX_CLIENT; i++) {
        s_client[i].sockfd = 0;
    }
    if ((listen(sockfd, MAX_CLIENT)) != 0) {
        perror_84("listen()");
    }
    serv = init_server(sockfd, max_sd, fds, serv);
    signal(SIGPIPE, SIG_IGN);
    return loop_server(s_client, serv);
}

int start_server(int port)
{
    struct sockaddr_in s_addr = {0};
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (port < 1 || port > 65534) {
        printf("port %d invalid please put a valid port (1 to 65534)\n", port);
        return 84;
    } else if (sockfd == -1) {
        perror_84("socket(): ");
    }
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
    &s_addr, sizeof(int)) == -1) {
        perror_84("setsockopt()");
    }
    if (bind(sockfd, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
        perror_84("bind()");
    }
    return run_server(sockfd, s_addr, port);
}