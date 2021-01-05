/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_strcmp.c
*/

int my_strcmp(char *s1, char *s2)
{
    int size_s1 = 0;
    int size_s2 = 0;
    int  size_ret = 0;

    for (int count = 0; s1[count] != '\0'; count++)
        size_s1 += s1[count] - 48;
    for (int count = 0; s2[count] != '\0'; count++)
        size_s2 += s2[count] - 48;
    size_ret = size_s1 - size_s2;
    if (size_ret != 0)
        return (size_ret);
    for (int count = 0; s1[count] != '\0' && s2[count] != '\0'; count++)
        if (s1[count] != s2[count])
            return (-1);
    return (0);
}