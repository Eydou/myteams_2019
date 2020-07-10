/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** file
*/

#include "server.h"
#include "logging_server.h"
#include "functions.h"

#include <sys/types.h>
#include <sys/stat.h>

static void setup_save_channel_file(void)
{
    FILE *file;
    bool check = false;
    char pass[256];

    if ((file = fopen("./save_file/save_channel.txt", "r")) != NULL) {
        check = true;
        fscanf(file, "%[^\n]", pass);
        if (strcmp("Channel69takeshi", pass) != 0)
            check = false;
    }
    if (check == false) {
        file = fopen("./save_file/save_channel.txt", "w+");
        fprintf(file, "Channel69takeshi\n\n\n");
    }
    fclose(file);
}

static void setup_save_file(void)
{
    FILE *file;
    bool check = false;
    char pass[256];

    if ((file = fopen("./save_file/save_user.txt", "r")) != NULL) {
        check = true;
        fscanf(file, "%[^\n]", pass);
        if (strcmp("JuiCY Booty Lo Lo!", pass) != 0)
            check = false;
    }
    if (check == false) {
        file = fopen("./save_file/save_user.txt", "w+");
        fprintf(file, "JuiCY Booty Lo Lo!\n\n\n");
    }
    fclose(file);
    setup_save_channel_file();
}

void is_save_file(void)
{
    FILE *file;
    bool check = false;
    char pass[256];
    struct stat st = {0};

    if (stat("./save_file", &st) == -1) {
        mkdir("./save_file", 0777);
    }
    if ((file = fopen("./save_file/save_team.txt", "r")) != NULL) {
        check = true;
        fscanf(file, "%[^\n]", pass);
        if (strcmp("Lopette Centipete999", pass) != 0)
            check = false;
    }
    if (check == false) {
        file = fopen("./save_file/save_team.txt", "w+");
        fprintf (file, "Lopette Centipete999\n\n\n");
    }
    fclose(file);
    setup_save_file();
}

void init_client_infile(client_serv_t *client, int id)
{
    FILE *file = fopen(USER_FILE, "a");

    fprintf(file,
    "name;%s\nuuid;%s\nstatus;1\nteam\nmessage\nchannel\n\n",
    client[id].user_name, client[id].uuid);
    fclose(file);
}

void load_user_infile(void)
{
    FILE *file = fopen(USER_FILE, "r");
    char line[2024];
    char **parse = {NULL};
    int count = -1;
    int len = 0;
    for (int i = 0; fgets(line, sizeof(line), file);) {
        i++;
        parse = split_str_client(line, parse , &len);
        if (i == 2 && len > 1) {
            for (int j = 0; j < len-1; j = j + 2) {
                server_event_user_loaded(delete_back(parse[j + 1]), parse[j]);
            }
            free_array(parse, len);
            fclose(file);
            return;
        }
        free_array(parse, len);
    }
    fclose(file);
}