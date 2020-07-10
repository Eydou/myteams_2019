/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_sub_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static int lens = 0;
static int number = 0;

void add_client_inteam(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(USER_FILE, "r");
    char line[2024];
    char **parse = {NULL};
    int count = -1;
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        parse = split_str_client(line, parse , &lens);
        if (i == count) {
            append_infile(USER_FILE, i, client[id].uuid_team);
            client[id].uuid_team = NULL;
            fclose(file);
            free_array(parse, lens);
            return;
        }
        for (int j = 0; j != lens; j++)
            if (!strcmp(parse[j], "name"))
                if (!strcmp(delete_back(parse[1]), client[id].user_name))
                    count = (i + 3);
        free_array(parse, lens);
    }
    fclose(file);
}

static bool check_user(client_serv_t client[MAX_CLIENT], int id, int nb,
char **parse)
{
    FILE *file = fopen(TEAM_FILE, "r");
    char line[2024];
    int count = -1;

    for (int j = 0; j != lens; j++) {
        if (!strcmp(parse[j], client[id].user_name)) {
            fclose(file);
            free_array(parse, lens);
            return true;
        }
    }
    fclose(file);
    return false;
}

static void setup_subscribe_team(client_serv_t client[MAX_CLIENT], int id
, FILE **file, char **parse)
{
    if (check_user(client, id, number, parse) == true) {
        dprintf(client[id].sockfd, "error;exist");
        fclose(*file);
    }
    dprintf(client[id].sockfd, "sub;%s;%s", client[id].uuid,
    client[id].command[1]);
    server_event_user_join_a_team(client[id].command[1],
    client[id].uuid);
    add_client_inteam(client, id);
    fclose(*file);
}

static void subscribe_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    FILE *file = fopen(TEAM_FILE, "r+");
    char line[2024];
    char **parse = {NULL};
    int count = -1;
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        parse = split_str_client(line, parse , &lens);
        if (i == count) {
            number = i;
            setup_subscribe_team(client, id, &file, parse);
            return;
        }
        for (int j = 0; j != lens; j++)
            if (!strcmp(parse[j], "uuid"))
                if (!strcmp(delete_back(parse[1]), client[id].command[1]))
                    count = (i + 2);
        free_array(parse, len);
    }
    dprintf(client[id].sockfd, "error;team;%s", client[id].command[1]);
    fclose(file);
}

void is_sub(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 2)
        dprintf(client[id].sockfd, "invalid command");
    else
        subscribe_client(client, id, len);
}