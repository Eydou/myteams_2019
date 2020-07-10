/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** feature_subed_clients
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"

static int lens;

static char *setup_search(client_serv_t client[MAX_CLIENT], int id,
char *nus, char **str)
{
    if (str[0] != NULL && !strcmp(str[0], "name")) {
        strcat(client[id].concat, delete_back(str[1]));
        strcat(client[id].concat, ";");
    } else if (str[0] != NULL && !strcmp(str[0], "uuid")) {
        strcat(client[id].concat, delete_back(str[1]));
        strcat(client[id].concat, ";");
    } else if (str[0] != NULL && !strcmp(str[0], "status")) {
        strcat(client[id].concat, delete_back(str[1]));
        strcat(client[id].concat, ";");
    }
    if (str[0] != NULL && !strcmp(delete_back(str[0]), "team")) {
        for (int i = 1; i != lens; i++)
            if (!strcmp(delete_back(str[i]), client[id].command[1])) {
                strcat(nus, client[id].concat);
            }
        memset(client[id].concat, 0, sizeof(client[id].concat));
    }
    return nus;
}

static void search_users_inteam(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(USER_FILE, "r");
    char line[2024];
    char *nus = my_calloc(1000);
    char **str = {NULL};
    int count = -1;
    client[id].concat = my_calloc(1000);
    strcat(nus, "user;");
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        str = split_str_client(line, str, &lens);
        nus = setup_search(client, id, nus, str);
    }
    nus[strlen(nus) - 1] = '\0';
    dprintf(client[id].sockfd, "%s", nus);
    fclose(file);
}

bool check_team_exists(client_serv_t client[MAX_CLIENT], int id)
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
                if (!strcmp(delete_back(parse[j]), client[id].command[1]))
                    return true;
        }
    }
    return false;
}

static void subscribed_clients(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (check_team_exists(client, id) == false) {
        dprintf(client[id].sockfd, "error;team;%s", client[id].command[1]);
    } else
        search_users_inteam(client, id);
}

void is_subed(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (len != 2)
        dprintf(client[id].sockfd, "invalid command");
    else
        subscribed_clients(client, id, len);
}