/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_unsub_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static int lens;

static bool close_file(bool check, FILE **file, FILE **file_T)
{
    fclose(*file);
    fclose(*file_T);
    remove(USER_FILE);
    rename("replace.tmp", USER_FILE);
    return check;
}

static bool delete_uuid_team(client_serv_t client[MAX_CLIENT], int id,
int count)
{
    FILE *file = fopen(USER_FILE, "r");
    FILE *file_T = fopen("replace.tmp", "w");
    char buffer[2024];
    bool check = false;
    char *team = strdup("team");
    char **parse = {NULL};
    for (int i = 0; fgets(buffer, sizeof(buffer), file);) {
        i++;
        if (i == count) {
            parse = split_str_client(buffer, parse , &lens);
            for (int j = 1; j != lens; j++)
                if (strcmp(delete_back(parse[j]), client[id].command[1]) != 0) {
                    strcat(team, ";");
                    strcat(team, parse[j]);
                } else if(!strcmp(delete_back(parse[j]), client[id].command[1]))
                    check = true;
                fprintf(file_T, "%s\n", team);
                } else
                fputs(buffer, file_T);
    }
    return close_file(check, &file, &file_T);
}

static bool unsubscribe_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    FILE *file = fopen(USER_FILE, "r");
    char line[2024];
    char **parse = {NULL};
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        parse = split_str_client(line, parse , &lens);
        for (int j = 0; j != lens; j++)
            if (!strcmp(parse[j], "name"))
                if (!strcmp(delete_back(parse[1]), client[id].user_name)) {
                    fclose(file);
                    return delete_uuid_team(client, id, i+3);
                }
        free_array(parse, lens);
    }
    fclose(file);
}

void is_unsub(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 2)
        dprintf(client[id].sockfd, "invalid command");
    else if (unsubscribe_client(client, id, len) == false)
        dprintf(client[id].sockfd, "error;team;%s", client[id].command[1]);
    else {
    dprintf(
    client[id].sockfd, "unsub;%s;%s", client[id].uuid, client[id].command[1]);
    server_event_user_leave_a_team(client[id].command[1], client[id].uuid);
    }
}