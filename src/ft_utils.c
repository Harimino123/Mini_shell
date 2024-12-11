/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:41:41 by hrasolof          #+#    #+#             */
/*   Updated: 2024/12/11 11:03:29 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t');
}

int ft_special_char(char c)
{
    return (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\t' || c == ':');
}

int     ft_search_until_egal(char *str, char *str_tocompare)
{
    int i;
    char *tmp = NULL;

    i = 0;
    while (str_tocompare[i] != '=')
        i++;
    tmp = malloc(sizeof(char *) * i);
    tmp = ft_strncpy(tmp, str_tocompare, i);
    if (ft_strcmp(tmp, str))
        return (0);
    else
        return (1);
}

int ft_contains_pipe(char **args)
{
    int i = 0;

    while (args[i]) {
        if (strcmp(args[i], "|") == 0)
            return 1; // Found a pipe
        i++;
    }
    return 0; // No pipe found
}