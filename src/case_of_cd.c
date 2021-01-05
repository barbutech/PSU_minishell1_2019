/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** case_of_cd.c
*/

#include "../include/my.h"
#include "../include/structures.h"
#include <stdio.h>

void case_of_home(char **env, char *elem)
{
    char *home;

    for (int line = 0; env[line] != NULL; line++) {
        if (my_strncmp(env[line], "HOME", 4) == 0)
            home = my_strndup(env[line], 5);
    }
    for (int line = 0; env[line] != NULL; line++) {
        if (my_strncmp(env[line], "PWD", 3) == 0) {
            env[line] = my_str_allocate_and_cat("PWD=", home);
        }
        if (my_strncmp(env[line], "OLDPWD", 6) == 0)
            env[line] = my_str_allocate_and_cat("OLDPWD=", elem);
    }
    if (chdir(home) == -1)
        perror("") ;
}

void case_of_cd_file(char **command, char **env, char *elem)
{
    if (my_strcmp(command[1], "-") == 0)
        return ;
    char *tmp = my_strdup(elem);
    elem = my_str_allocate_and_cat(elem, "/");
    elem = my_str_allocate_and_cat(elem, command[1]);

    if (chdir(elem) == -1) {
        perror(command[1]);
        return ;
    }
    for (int line = 0; env[line] != NULL; line++) {
        if (my_strncmp(env[line], "PWD", 3) == 0)
            env[line] = my_str_allocate_and_cat("PWD=", elem);
        if (my_strncmp(env[line], "OLDPWD", 6) == 0)
            env[line] = my_str_allocate_and_cat("OLDPWD=", tmp);
        }
}

void case_of_cd_malus(char **command, char **env, char *elem, char *old_elem)
{
    if (my_strcmp(command[1], "-") != 0)
        return ;
    for (int line = 0; env[line] != NULL; line++) {
        if (my_strncmp(env[line], "PWD", 3) == 0)
            env[line] = my_str_allocate_and_cat("PWD=", old_elem);
        if (my_strncmp(env[line], "OLDPWD", 3) == 0)
            env[line] = my_str_allocate_and_cat("OLDPWD=", elem);
    }
        if (chdir(old_elem) == -1)
        perror("") ;
}

int case_of_cd(char **command, char **env)
{
    int size_command = 0;
    char *elem;
    char *old_elem;
    char *home;

    for (; command[size_command] != NULL; size_command++);
    if (size_command > 2)
        return (84);
    for (int line = 0; env[line] != NULL; line++) {
        if (my_strncmp(env[line], "PWD", 3) == 0)
            elem = my_strndup(env[line], 4);
        if (my_strncmp(env[line], "OLDPWD", 6) == 0)
            old_elem = my_strndup(env[line], 7);
    }
    if (size_command == 1 || command[1] && my_strcmp(command[1], "~") == 0) {
        case_of_home(env, elem);
        return (0);
    }
    case_of_cd_file(command, env, elem);
    case_of_cd_malus(command, env, elem, old_elem);
}