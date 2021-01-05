/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** environment.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/structures.h"
#include "../include/my.h"

void set_value(char **envp, int count, int line, name_t **value)
{
    int tempo = 0;
    int save = count;
    char *elem;

    for (; envp[line][count] != '\0'; tempo++, count++);
            elem = malloc(sizeof(char) * (tempo + 1));
            elem[tempo] = '\0';
            save++;
        for (int lenght_elem = 0; lenght_elem < tempo; save++, lenght_elem++)
            elem[lenght_elem] = envp[line][save];
        stack_push(value, elem);
}

name_t *fill_name(name_t *name, char **envp, name_t **value)
{
    char *elem;
    int count = 0;
    name_t *ret = NULL;

    for (int line = 0; envp[line] != NULL; line++) {
        for (; envp[line][count] != '='; count++);
        elem = malloc(sizeof(char) * (count + 1));
        elem[count] = '\0';
        for (int tmp = 0; tmp < count; tmp++)
            elem[tmp] = envp[line][tmp];
        stack_push(&ret, elem);
        set_value(envp, count, line, value);
        count = 0;
    }
    return (ret);
}

int case_of_setenv(char **command, name_t **name, name_t **value)
{
    if (!(command[1]))
        return (-1);
    (*name) = (*name)->head;
    (*value) = (*value)->head;
    for (; (*name);) {
        if (there_is_a_value(name, value, command) == 0)
            return 0;
        if (!((*name)->next))
            break;
        (*name) = (*name)->next;
        (*value) = (*value)->next;
    }
    stack_push(name, command[1]);
    if (command[2])
        stack_push(value, command[2]);
    else
        stack_push(value, "");
    return (0);
}

void case_of_env(name_t *name, name_t *value)
{
    name = name->head;
    value = value->head;
    for (; name; name = name->next, value = value->next) {
        my_putstr(name->name);
        write(1, "=", 1);
        my_putstr(value->name);
        write(1, "\n", 1);
        if (name->next == NULL)
            return;
    }
    return ;
}

void case_of_unsetenv(char **command, name_t **name, name_t **value)
{
    (*name) = (*name)->head;
    (*value) = (*value)->head;
    for (; name; (*name) = (*name)->next, (*value) = (*value)->next) {
        if (my_strcmp(command[1], (*name)->name) == 0) {
            stack_pop(name);
            stack_pop(value);
            return ;
        }
        if ((*name)->next == NULL)
            return ;
    }
}