/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_list_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static void list_channel(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(TEAM_FILE, "r+");
    char line[2024];
    char *nus = strdup("list;channel;");
    char **str = {NULL};
    int len = 0;
    int i = 0;
    for (; fgets(line, sizeof(line), file);) {
        i++;
        str = split_str_client(line, str, &len);
        if (str[0] != NULL && str[1] != NULL && !strcmp(str[0],"name_channel")||
            str[0] != NULL && str[1] != NULL && !strcmp(str[0], "uuid") ||
            str[0] != NULL && str[1] != NULL && !strcmp(str[0],
            "description")) {
            strcat(nus, delete_back(str[1]));
            strcat(nus, ";");
        }
    }
    (i == 3) ? dprintf(client[id].sockfd, "no channel available") :
    dprintf(client[id].sockfd, "%s", delete_back(nus));
    fclose(file);
}

static void list_team(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(TEAM_FILE, "r+");
    char line[2024];
    char *nus = strdup("list;team;");
    char **str = {NULL};
    int len = 0;
    int i = 0;
    for (; fgets(line, sizeof(line), file);) {
        i++;
        str = split_str_client(line, str, &len);
        if (str[0] != NULL && str[1] != NULL && !strcmp(str[0], "name_team") ||
            str[0] != NULL && str[1] != NULL && !strcmp(str[0], "uuid") ||
            str[0] != NULL && str[1] != NULL && !strcmp(str[0],
            "description")) {
            strcat(nus, delete_back(str[1]));
            strcat(nus, ";");
        }
    }
    (i == 3) ? dprintf(client[id].sockfd, "no team available") :
    dprintf(client[id].sockfd, "%s", delete_back(nus));
    fclose(file);
}

void is_list(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 1) {
        dprintf(client[id].sockfd, "invalid command");
        return;
    }
    if (client[id].use == 0)
        list_team(client, id);
    if (client[id].use == 1)
        list_channel(client, id);
}