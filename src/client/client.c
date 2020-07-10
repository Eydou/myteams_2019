/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#include "client.h"
#include "functions.h"
#include "logging_client.h"

#include <signal.h>
#include <errno.h>

static void handle_signal_action(int sig_number)
{
    run = 0;
}

static s_client_t *init_client(s_client_t *client)
{
    client = malloc(sizeof(s_client_t));
    client->login = false;
    client->user_name = NULL;
    client->uuid = NULL;
    return client;
}

static void read_client(int sockfd, s_client_t *client)
{
    int len = 0;
    char buffer[5024];

    if ((len = recv(sockfd, buffer, 1024 - 1, 0)) < 0)
        perror_84("recv()");
    buffer[len] = 0;
    if (!len) {
        close(sockfd);
        exit(0);
    }
    if (!strcmp(buffer, "end_client")) {
        if (client->login != false)
            client_event_loggedout(client->uuid, client->user_name);
        close(client->sokfd);
        free(client);
        exit(0);
    }
    command_management(buffer, client);
}

static void loop_client(int sockfd, s_client_t *client)
{
    fd_set fds;
    client->sokfd = sockfd;

    signal(SIGINT, handle_signal_action);
    for (;run != 0;) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(sockfd, &fds);
        if (select(sockfd + 1, &fds, NULL, NULL, NULL) == -1)
            if (errno == EINTR)
                continue;
            else
                perror_84("select()");
        if (FD_ISSET(STDIN_FILENO, &fds))
            send_client(client, get_next_line(0));
        else if (FD_ISSET(sockfd, &fds))
            read_client(sockfd, client);
    }
    printf("\n");
    logout_client(client, "/logout");
}

int start_client(char *ip, int port)
{
    s_client_t *s_client = init_client(s_client);
    struct hostent *info;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr = {0};
    (sockfd) ? 0 : exit(84);
    if (port < 1 || port > 65534) {
        return 84;
    }
    if ((info = gethostbyname(ip)) == NULL) {
        perror_84("invalid ip");
    }
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
        perror_84("connect()");
    loop_client(sockfd, s_client);
    free(s_client);
    return 0;
}
