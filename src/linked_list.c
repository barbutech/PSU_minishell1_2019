/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** linked_list.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/structures.h"
#include "../include/my.h"

void stack_push(name_t **name, char *elem)
{
    name_t *new = malloc(sizeof(name_t));

    new->name = elem;
    if ((*name) == NULL) {
        new->next = NULL;
        (*name) = new;
        (*name)->head = (*name);
        return ;
    }
    new->next = NULL;
    new->prev = (*name);
    new->prev->next = new;
    new->head = (*name)->head;
    (*name) = new;
    return ;
}

void stack_pop(name_t **name)
{
    if ((*name) == NULL)
        return ;
    if ((*name)->next != NULL) {
        (*name)->next->prev = (*name)->prev;
        (*name)->prev->next = (*name)->next;
    }
    (*name) = (*name)->prev;
    (*name)->next = NULL;
}

char **new_environment(name_t *name, name_t *value)
{
    int size = 0;
    char **env;

    name = name->head;
    value = value->head;
    for (; name->next; name = name->next, size++);
    name = name->head;
    size++;
    env = malloc(sizeof(char *) * (size + 1));
    if (env == NULL)
        return (NULL);
    env[size] = NULL;
    for (int line = 0; env[line] != NULL; line++)
        env[line] = my_str_allocate_and_cat(name->name, value->name);
    return (env);
}

void error(char **envp)
{
    int count = 0;

    for (; envp[count]; count++);
    if (count < 2)
        exit (EXIT_SUCCESS);
}

int there_is_a_value(name_t **name, name_t **value, char **command)
{
    if (my_strcmp((*name)->name, command[1]) == 0) {
        if (command[2])
            (*value)->name = my_strdup(command[2]);
        else
            (*value)->name = "";
        return (0);
    }
    return (1);
}