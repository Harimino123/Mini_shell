/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:14:53 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/28 14:48:33 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static size_t   word_count(const char *str)
{
    size_t  i;
    size_t  w_count;
    
    i = 0;
    w_count = 0;
    while (str[i])
    {
        while (str[i] && ft_isspace(str[i]))
            i++;
        if (str[i] && !ft_special_char(str[i]))
        {
            w_count++;
            while (str[i] && !ft_special_char(str[i]))
                i++;
        }
        while (str[i] && ft_special_char(str[i]))
            i++;
    }
    return (w_count);
}

void ft_assigne(t_datatok *data, const char *str)
{
    data->w_len = word_count(str);
    data->out = malloc(sizeof(char *) * (data->w_len + 1));
    if (!data->out)
        exit (EXIT_FAILURE);
    data->index = 0;
    data->tab_i = 0;
}

int extract_word(t_datatok *data, const char *str)
{
    size_t len;
    int in_quotes;

    in_quotes = 0;
    if (str[data->index] == '"')
        in_quotes = 1;
    else if (str[data->index] == '\'')
        in_quotes = 2;
    if (in_quotes)
        data->index++;
    data->index2 = data->index;
    while (str[data->index] && ((in_quotes && 
    ((in_quotes == 1 && str[data->index] != '"') || 
    (in_quotes == 2 && str[data->index] != '\''))) || 
    (!in_quotes && !ft_isspace(str[data->index]) && !ft_special_char(str[data->index]))))
        data->index++;
    len = data->index - data->index2;
    data->out[data->tab_i] = malloc(sizeof(char) * (len + 1));
    if (!data->out[data->tab_i])
    {
        free_tab_struct(data);
        return (0);
    }
    ft_strncpy(data->out[data->tab_i], &str[data->index2], len);
    data->out[data->tab_i++][len] = '\0';
    if (in_quotes && (str[data->index] == '"' || str[data->index] == '\''))
        data->index++;
    return (1);
}

char **ft_toksplit(const char *str)
{
    t_datatok   data;

    if (!str)
        return (NULL);
    ft_assigne(&data, str);
    while (str[data.index])
    {
        while (str[data.index] && (ft_isspace(str[data.index]) ||
         ft_special_char(str[data.index])))
            data.index++;
        if (str[data.index] && !ft_isspace(str[data.index]) &&
         !ft_special_char(str[data.index]))
        {
            if (!extract_word(&data, str))
                return (NULL);
        }
    }
    data.out[data.tab_i] = NULL;
    return (data.out);
}


