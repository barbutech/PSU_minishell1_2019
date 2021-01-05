/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** my.h
*/

#include <unistd.h>
#include "structures.h"

int my_putstr(char *);
char ** my_str_to_word_array(char *);
char *my_getenv(name_t *, name_t *, char *, char **);
char *my_str_allocate_and_cat(char *, char *);
int my_strcmp(char *, char *);
void stack_push(name_t **, char *);
void stack_pop(name_t **);
name_t *fill_name(name_t *, char **, name_t **);
void case_of_env(name_t *, name_t *);
void case_of_unsetenv(char **, name_t **, name_t **);
int case_of_setenv(char **, name_t **, name_t **);
int my_strlen(char *);
char *my_strdup(char *str);
char **new_environment(name_t *, name_t *);
int my_strncmp(char *, char *, int);
int case_of_cd(char **command, char **env);
void case_of_cd_malus(char **, char **, char *, char *);
void case_of_cd_file(char **, char **, char *);
char *my_strndup(char *, int);
void error(char **);
int there_is_a_value(name_t **, name_t **, char **);