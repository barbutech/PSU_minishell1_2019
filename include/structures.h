/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** structures.h
*/

#ifndef structures_h
#define structures_h

struct name
{
    char *name;
    int last_return;
    struct name *head;
    struct name *next;
    struct name *prev;
};
typedef struct name name_t;

#endif