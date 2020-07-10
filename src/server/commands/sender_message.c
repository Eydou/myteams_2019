/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** sender_message
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static void send_message_infile(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(USER_FILE, "r+");
    char line[2024];
    char **parse = {NULL};
    int count = -1;
    int len = 0;
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        parse = split_str_client(line, parse , &len);
        if (i == count) {
            append_infile(USER_FILE, count, client[id].uuid);
            append_infile(USER_FILE, count, client[id].command[2]);
            append_infile(USER_FILE, count, itoa((int)time(NULL)));
            free_array(parse, len);
            fclose(file);
            return;
        }
        for (int j = 0; j != len; j++)
            if (!strcmp(parse[j], "uuid"))
                if (!strcmp(delete_back(parse[1]), client[id].command[1]))
                    count = (i + 3);
    }
}

static void sending_message(client_serv_t client[MAX_CLIENT], int id)
{
    server_event_private_message_sended(client[id].uuid, client[id].command[1],
    client[id].command[2]);
    for (int i = 0; i != MAX_CLIENT; i++) {
        if (i != id && client[i].login == true) {
            if (!strcmp(client[id].command[1], client[i].uuid))
                dprintf(client[i].sockfd, "message;%s;%s",
                client[id].uuid, client[id].command[2]);
        }
    }
}

bool is_user_exist(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(USER_FILE, "r+");
    char line[5024];
    char **parse = {NULL};
    int len = 0;
    for (int count = 0; fgets(line, sizeof(line), file);) {
        count++;
        if (count == 2) {
            parse = split_str_client(line, parse, &len);
            for (int j = 0; j != len; j++) {
                if (!strcmp(delete_back(parse[j]), client[id].command[1])
                && strlen(client[id].command[1]) == 36) {
                    fclose(file);
                    free_array(parse, len);
                    return true;
                }
            }
        }
    }
    free_array(parse, len);
    fclose(file);
    return false;
}

void send_message_user(client_serv_t client[MAX_CLIENT], int id)
{
    if (is_user_exist(client, id) == false)
        dprintf(client[id].sockfd, "error;user;%s", client[id].command[1]);
    else if (!strcmp(client[id].command[1], client[id].uuid) ||
    strlen(client[id].command[1]) > MAX_BODY_LENGTH)
        dprintf(client[id].sockfd, "error;unauthoriz", client[id].command[1]);
    else {
        sending_message(client, id);
        send_message_infile(client, id);
    }
}