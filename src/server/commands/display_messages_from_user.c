/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** display_messages_from_user
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static void setup_display_message_infile(client_serv_t client[MAX_CLIENT],
int id, char **parse, int len)
{
    bool check = false;

    for (int i = 0; i != len; i++) {
        if (!strcmp(parse[i], client[id].command[1])) {
            dprintf(client[id].sockfd,
            "display_message;%s;%s;%s", parse[i], parse[i + 1], parse[i + 2]);
            check = true;
            i = i + 2;
        }
        usleep(200);
    }
    if (check == false)
        dprintf(client[id].sockfd, "error;user;%s", client[id].command[1]);
}

static void display_message_infile(client_serv_t client[MAX_CLIENT], int id)
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
            setup_display_message_infile(client, id, parse, len);
            free_array(parse, len);
            fclose(file);
            return;
        }
        for (int j = 0; j != len; j++)
            if (!strcmp(parse[j], "uuid"))
                if (!strcmp(delete_back(parse[1]), client[id].uuid))
                    count = (i + 3);
    }
}

void display_message_user(client_serv_t client[MAX_CLIENT], int id)
{
    if (is_user_exist(client, id) == false)
        dprintf(client[id].sockfd, "error;user;%s", client[id].command[1]);
    else
        display_message_infile(client, id);
}