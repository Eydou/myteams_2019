/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_create_channel_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

#include <uuid/uuid.h>

static void append_channel_infile(client_serv_t client[MAX_CLIENT], int id)
{
    uuid_t binuuid;
    char *uuid = malloc(37);
    FILE *file;
    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    append_infile(CHANNEL_FILE, 2, client[id].command[1]);
    append_infile(CHANNEL_FILE, 2, uuid);
    file = fopen(CHANNEL_FILE, "a");
    fprintf(file, "name_channel;%s\nuuid;%s\ndescription;%s\nteam;%s\
thread\n\n", client[id].command[1],
    uuid, client[id].command[2], client[id].uuid_team);
    dprintf(client[id].sockfd, "create_channel;%s;%s;%s",
    uuid, client[id].command[1], client[id].command[2]);
    server_event_channel_created(uuid, client[id].uuid_team,
    client[id].command[1]);
    client[id].uuid_chan = strdup(uuid);
    add_client_inteam(client, id);
    fclose(file);
}

static bool check_channel_exist(client_serv_t client[MAX_CLIENT], int id)
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
                if (!strcmp(delete_back(parse[j]), client[id].command[1])) {
                    dprintf(client[id].sockfd, "error;exist");
                    return true;
                }
        }
    }
    return false;
}

void create_channel(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (strlen(client[id].command[1]) > MAX_NAME_LENGTH ||
    strlen(client[id].command[2]) > MAX_DESCRIPTION_LENGTH)
        dprintf(client[id].sockfd, "invalid command");
    else if (check_channel_exist(client, id) == false) {
        append_channel_infile(client, id);
    }
}
