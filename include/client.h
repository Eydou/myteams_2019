/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <string.h>
#include <stdbool.h>
#include <signal.h>

typedef struct s_client
{
    bool login;
    int sokfd;
    char *uuid;
    char *user_name;
} s_client_t;

static volatile sig_atomic_t run = 1;

typedef void (*command)(char *message, char **command, s_client_t *client,
int len);

int start_client(char *ip, int port);
void send_client(s_client_t *client, char *message);
void logout_client(s_client_t *client, char *message);

void command_management(char *message, s_client_t *client);

void is_user(char *message, char **command, s_client_t *client, int);
void is_users(char *message, char **command, s_client_t *client, int);
void is_log(char *message, char **command, s_client_t *client, int);
void is_close(char *message, char **command, s_client_t *client, int);
void is_error(char *message, char **command, s_client_t *client, int);
void is_message_private(char *message, char **command, s_client_t *client,
int);
void is_display_message(char *message, char **command, s_client_t *client,
int len);
void is_create_team(char *message, char **command, s_client_t *client,
int len);
void is_create_channel(char *message, char **command, s_client_t *client,
int len);
void is_subscribe(char *message, char **command, s_client_t *client,
int len);
void is_unsubscribe(char *message, char **command, s_client_t *client,
int len);
void is_subed(char *message, char **command, s_client_t *client,
int len);
void is_list(char *message, char **command, s_client_t *client,
int len);


#endif /* !CLIENT_H_ */
