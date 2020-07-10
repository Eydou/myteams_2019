/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** setup_feature_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

#include <uuid/uuid.h>

static bool check_team_exist(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(TEAM_FILE, "r");
    char line[5024];
    char **parse = {NULL};
    int len = 0;

    for (int count = 0; fgets(line, sizeof(line), file);) {
        count++;
        if (count == 2) {
            parse = split_str_client(line, parse, &len);
            for (int j = 0; j != len; j++)
                if (!strcmp(delete_back(parse[j]), client[id].command[1])) {
                    dprintf(client[id].sockfd, "error;exist");
                    return true;
                }
        }
    }
    return false;
}

static void append_team_infile(client_serv_t client[MAX_CLIENT], int id)
{
    uuid_t binuuid;
    char *uuid = malloc(37);
    FILE *file;
    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    append_infile(TEAM_FILE, 2, client[id].command[1]);
    append_infile(TEAM_FILE, 2, uuid);
    file = fopen(TEAM_FILE, "a");
    fprintf(file, "name_team;%s\nuuid;%s\ndescription;%s\npeople;%s\n\
thread\nchannel\n\n", client[id].command[1],
    uuid, client[id].command[2], client[id].user_name);
    dprintf(client[id].sockfd, "create_team;%s;%s;%s",
    uuid, client[id].command[1], client[id].command[2]);
    server_event_team_created(uuid, client[id].command[1],
    client[id].uuid);
    client[id].uuid_team = strdup(uuid);
    fclose(file);
}

static void create_team(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (strlen(client[id].command[1]) > MAX_NAME_LENGTH ||
    strlen(client[id].command[2]) > MAX_DESCRIPTION_LENGTH)
        dprintf(client[id].sockfd, "invalid command");
    else if (check_team_exist(client, id) == false) {
        append_team_infile(client, id);
    }
}

void is_create(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (client[id].use == 0 && len == 3)
        create_team(client, id, len);
    else if (client[id].use == 1 && len == 3) {
        create_channel(client, id, len);
    } else
        dprintf(client[id].sockfd, "invalid command");
}