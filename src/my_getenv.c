/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_getenv.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/structures.h"
#include "../include/my.h"

char *my_getenv(name_t *value, name_t *name, char *elem, char **command)
{
    char *path;
    int count = 0;
    char **pathes;
    char *ret;

    name = name->head;
    value = value->head;
    for (; my_strcmp(name->name, elem) != 0;) {
        if (name->next == NULL)
        return (NULL);
        name = name->next;
        value = value->next;
    }
    for (; value->name[count] != '\0'; count++);
    path = malloc(sizeof(char) * (count + 1));
    path[count] = '\0';
    for (int mem = 0; value->name[mem] != '\0'; mem++)
        path[mem] = value->name[mem];
    return (path);
}