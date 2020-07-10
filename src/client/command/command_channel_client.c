/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_channel_client
*/

#include "client.h"
#include "functions.h"
#include "logging_client.h"

void is_create_channel(char *message, char **command, s_client_t *client,
int len)
{
    client_event_channel_created(command[1], command[2], command[3]);
}