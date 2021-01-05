/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** my_str_to_word_array.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int number_of_words(char *str)
{
    int nbr_of_words = 0;
    int count = 0;

    for (; str[count] != '\0'; count++) {
        for (; str[count] == ':' || str[count] == ' ' ||
        str[count] == '\t'; count++);
        for (; str[count] != ':' && str[count] != ' ' &&
        str[count] != '\0' && str[count] != '\t'; count++);
        nbr_of_words++;
        if (str[count] == '\0')
            return (nbr_of_words);
        for (; str[count] == ':' || str[count] == ' ' ||
        str[count] == '\t'; count++);
    }
    return (nbr_of_words);
}

char *fill_line(char *str, int count, int nbr, int tmp)
{
    int pos = 0;
    char *ret = malloc(sizeof(char) * (nbr + 1));

    if (ret == NULL)
        return (NULL);
    for (; tmp < count; tmp++, pos++) {
        for (;str[tmp] == '\t' || str[tmp] == ' '; tmp++);
            ret[pos] = str[tmp];
    }
    ret[pos] = '\0';
    return (ret);
}

char *fill_tab(char *str, char **word_tab, int p)
{
    static int count = 0;
    static int tmp = 0;
    int nbr = 0;

    for (; str[count] == ':' || str[count] == ' ' ||
    str[count] == '\t'; count++);
    for (;str[count] != ' ' && str[count] != ':' &&
    str[count] != '\0' && str[count] != '\n' && str[count] != '\t'; count++)
        nbr++;
    word_tab[p] = fill_line(str, count, nbr, tmp);
    for (;str[count] == ' ' || str[count] == ':' ||
    str[count] == '\n' || str[count] == '\t'; count++);
    tmp = count;
    if (str[count] == '\0') {
        count = 0;
        tmp = 0;
    }
    return (word_tab[p]);
}

char **my_str_to_word_array(char *str)
{
    int nbr_of_words = number_of_words(str);
    char **word_tab = malloc(sizeof(char *) * (nbr_of_words + 1));

    if (word_tab == NULL)
        return (NULL);
    word_tab[nbr_of_words] = NULL;
    for (int count = 0; count < nbr_of_words; count++) {
        fill_tab(str, word_tab, count);
    }
    return (word_tab);
}