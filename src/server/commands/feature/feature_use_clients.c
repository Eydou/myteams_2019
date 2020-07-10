/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_use_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

bool check_is_user_inteam(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(USER_FILE, "r");
    char line[2024];
    char *nus = strdup("users;");
    char **str = {NULL};
    int count = -1;
    int len = 0;
    client[id].concat = my_calloc(1000);
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        str = split_str_client(line, str, &len);
        if (str[0] != NULL && len > 1 && !strcmp(delete_back(str[0]), "team"))
        for (int j = 1; j != len; j++)
            if (!strcmp(delete_back(str[j]), client[id].command[1])) {
                fclose(file);
                return true;
            }
    }
    fclose(file);
    return false;
}

bool check_channel_exists(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(CHANNEL_FILE, "r");
    char line[5024];
    char **parse = {NULL};
    int len = 0;

    for (int count = 0; fgets(line, sizeof(line), file);) {
        count++;
        if (count == 2) {
            parse = split_str_client(line, parse, &len);
            for (int j = 0; j != len; j++)
                if (!strcmp(delete_back(parse[j]), client[id].command[2]))
                    return true;
        }
    }
    return false;
}

static void setup_use(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    bool check = false;

    if (len == 3) {
        if (check_team_exists(client, id) == true) {
            if (check_is_user_inteam(client, id) == true)
                if (check_channel_exists(client, id) == true) {
                    client[id].use = 2;
                    check = true;
                    client[id].uuid_team = strdup(client[id].command[1]);
                    client[id].uuid_chan = strdup(client[id].command[2]);
                }
        }
        if (check == false)
            dprintf(client[id].sockfd, "error;unauthoriz");
    }
}

void is_use(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len == 1) {
        client[id].user_name = NULL;
        client[id].uuid_chan = NULL;
        client[id].use = 0;
    }
    if (len == 2) {
        if (check_team_exists(client, id) == true) {
            if (check_is_user_inteam(client, id) == true) {
                client[id].uuid_team = strdup(client[id].command[1]);
                client[id].use = 1;
            } else
                dprintf(client[id].sockfd, "error;unauthoriz");
        }
    }
    setup_use(client, id, len);
}