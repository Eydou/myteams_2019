/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_user
*/

#include "server.h"
#include "functions.h"
#include "logging_server.h"
#include <uuid/uuid.h>

char *delete_back(char *uuid)
{
    for (int i = 0; uuid[i] != '\0'; i++) {
        if (uuid[i] == '\n' || uuid[i] == '\r')
            uuid[i] = '\0';
    }
    return uuid;
}

static void assign_user_to_client(int id, int nb_line, char *occ,
client_serv_t *client)
{
    FILE *file = fopen(USER_FILE, "r+");
    char line[2024];
    char **user = NULL;
    int len = 0;

    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        if (i == nb_line) {
            user = split_str_client(line, user, &len);
            for (int i = 0; user[i] != NULL; i++) {
                if (!strcmp(user[i], occ)) {
                    client[id].user_name = user[i];
                    client[id].uuid = delete_back(user[i + 1]);
                    fclose(file);
                    return;
                }
            }
        }
    }
    fclose(file);
}

void share_log_client(client_serv_t client[MAX_CLIENT], int id)
{
    for (int i = 0; i != MAX_CLIENT; i++) {
        if (i != id) {
            if (client[i].login == true)
                dprintf(client[i].sockfd, "log;%s;%s", client[id].user_name,
                client[id].uuid);
        }
    }
}

void create_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    uuid_t binuuid;
    char *uuid = malloc(37);

    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    append_infile(USER_FILE, 2, client[id].command[1]);
    append_infile(USER_FILE, 2, uuid);
    server_event_user_created(uuid, client[id].command[1]);
    server_event_user_logged_in(uuid);
    client[id].login = true;
    client[id].uuid = uuid;
    client[id].user_name = client[id].command[1];
    dprintf(client[id].sockfd, "login;%s;%s", client[id].command[1], uuid);
    share_log_client(client, id);
}

void login_client(client_serv_t client[MAX_CLIENT], int id,
int len)
{
    if (strlen(client[id].command[1]) > MAX_NAME_LENGTH ||
    !strcmp(client[id].command[1], ""))
        dprintf(client[id].sockfd, "Please enter a valid login");
    else if (check_occurence(USER_FILE, 2, client[id].command[1]) == false) {
        create_client(client, id, len);
        init_client_infile(client, id);
        client[id].login = true;
    } else if (check_occurence(USER_FILE, 2, client[id].command[1]) == true) {
        assign_user_to_client(id, 2, client[id].command[1], client);
        server_event_user_logged_in(client[id].uuid);
        share_log_client(client, id);
        dprintf(client[id].sockfd, "login;%s;%s", client[id].user_name,
        client[id].uuid);
        client[id].login = true;
        status_client(client, id, 1);
    }
}
