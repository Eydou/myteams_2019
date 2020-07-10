/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_infile
*/

#include "server.h"
#include "functions.h"

void send_commands_users(client_serv_t client[MAX_CLIENT], int id)
{
    FILE *file = fopen(USER_FILE, "r+");
    char line[2024];
    char *nus = strdup("users;");
    char **str = {NULL};
    int count = -1;
    int len = 0;
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        str = split_str_client(line, str, &len);
        if (str[0] != NULL && str[1] != NULL && !strcmp(str[0], "name") ||
            str[0] != NULL && str[1] != NULL && !strcmp(str[0], "uuid") ||
            str[0] != NULL && str[1] != NULL && !strcmp(str[0], "status")) {
            str[1][strlen(str[1])-1] = 0;
            strcat(nus, str[1]);
            strcat(nus, ";");
        }
    }
    nus[strlen(nus)-1] = 0;
    dprintf(client[id].sockfd, "%s", nus);
    fclose(file);
}

static void replace_status(char *number, int nb_line, int status)
{
    FILE * file = fopen(USER_FILE, "r");
    FILE * f_temp = fopen("replace.txt", "w");
    char line[1024];
    int nb;
    if (status != -1)
    number[strlen(number) - 1] = '\0';
    nb = atoi(number);
    if (status == 1)
        nb++;
    else if (status != -1)
        nb = nb - 1;
    for (int count = 0; (fgets(line, sizeof(line), file)) != NULL;) {
        count++;
        count == nb_line ? fprintf(f_temp, "status;%d\n", nb) :
        fputs(line, f_temp);
    }
    fclose(file);
    fclose(f_temp);
    remove(USER_FILE);
    rename("replace.txt", USER_FILE);
}

void status_client(client_serv_t client[MAX_CLIENT], int id, int status)
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
            replace_status(parse[1], count, status);
            free_array(parse, len);
            fclose(file);
            return;
        }
        for (int j = 0; j != len; j++)
            if (!strcmp(parse[j], "name")) {
                if (!strcmp(delete_back(parse[1]), client[id].user_name))
                    count = (i + 2);
            }
        free_array(parse, len);
    }
}

void close_status_client(void)
{
    FILE *file = fopen(USER_FILE, "r+");
    char line[2024];
    char **parse = {NULL};
    int count = -1;
    int len = 0;
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        parse = split_str_client(line, parse, &len);
        for (int j = 0; j != len; j++)
            if (!strcmp(parse[0], "status")) {
                replace_status("0", i, -1);
            }
    }
}