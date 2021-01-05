/*
** EPITECH PROJECT, 2019
** Minishell1
** File description:
** minishell.c
*/

#define WEXITSTATUS
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "../include/my.h"
#include "../include/structures.h"

char *is_ok(char **command, name_t *value, name_t *name)
{
    char *path = my_getenv(value, name, "PATH", command);
    char *ret;
    char **the_pathes = my_str_to_word_array(path);

    if (the_pathes == NULL)
        return (NULL);
    for (int line = 0; the_pathes[line] != NULL; line++) {
        ret = my_str_allocate_and_cat(the_pathes[line], "/");
        ret = my_str_allocate_and_cat(ret, command[0]);
        if (access(ret, F_OK) == 0)
            return (ret);
        free(ret);
    }
    return (command[0]);
}

int execve_part(char **command, char *way, char **envp, int stat_loc)
{
    __pid_t pid_son;

    pid_son = fork();
        if (pid_son == 0) {
            if (execve(way, command, envp) == -1)
                my_putstr(way);
                write(2, ": Command not found.\n", 21);
                kill(pid_son, 0);
                exit (EXIT_SUCCESS);
        }
        else
            waitpid(pid_son, &stat_loc, 0);
    return (stat_loc);
}

int exec_for_me(char *way, char **command, char **envp)
{
    int stat_loc = 0;
    int size = 0;
    int line = 0;

    if (my_strcmp(command[0], "setenv") == 0 ||
    my_strcmp(command[0], "unsetenv") == 0)
        return (0);
    if (my_strcmp(command[0], "env") != 0 &&
    command[0][0] != '\0' && my_strcmp(command[0], "cd") != 0) {
        stat_loc = execve_part(command, way, envp, stat_loc);
        if (stat_loc == 139)
            write(2, "Segmentation fault\n", 19);
        if (stat_loc == 136)
            write(2, "segmentation fault [floating point]\n", 36);
        return (WEXITSTATUS(stat_loc));
    }
}

void builtins(char **command, name_t **name, name_t **value, char **envp)
{
    int size_command = 0;

    for (; command[size_command] != NULL; size_command++);

    if (my_strcmp(command[0], "exit") == 0) {
        write (1, "exit\n", 5);
        exit (EXIT_SUCCESS);
    }
    if (my_strcmp(command[0], "env") == 0)
        case_of_env((*name), (*value));
    if (my_strcmp(command[0], "setenv") == 0)
        if (size_command == 1)
            case_of_env((*name), (*value));
        else
            case_of_setenv(command, name, value);
    if (my_strcmp(command[0], "unsetenv") == 0 && size_command == 2)
        case_of_unsetenv(command, name, value);
    if (my_strcmp(command[0], "cd") == 0)
        case_of_cd(command, envp);
}

int main (int argc, char **argv, char **envp)
{
    error(envp);
    char *answer = NULL;
    ssize_t n = 0;
    char **command;
    char *way;
    name_t *value = NULL;
    name_t *name = fill_name(name, envp, &value);

    while (1) {
        write(0, "\e[36mprompt_t>:\e[0m", 19);
        if (getline(&answer, &n, stdin) == EOF)
            return (name->last_return);
        command = my_str_to_word_array(answer);
        if (command == NULL)
            return (84);
        way = is_ok(command, value, name);
        builtins(command, &name, &value, envp);
        name->last_return = exec_for_me(way, command, envp);
    }
}