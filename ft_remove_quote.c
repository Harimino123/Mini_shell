/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:54:21 by hrasolof          #+#    #+#             */
/*   Updated: 2024/10/30 18:17:11 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void ft_remove_quote(char   **args)
{
    size_t  i;
    size_t  len;

    i = 0;
    while (args[i])
    {
        len = ft_strlen(args[i]);
        if ((args[i][0] == '"' && args[i][len - 1] == '"') || (args[i][0] == '\'' && args[i][len - 1] == '\''))
        {
            char *result = (char *)malloc(len - 1);
            if (!result)
                return ;
            ft_memcpy(result, args[i] + 1, len - 2);
            result[len - 2] = '\0';
            free (args[i]);
            args[i] = result;
            printf("<%s>\n", args[i]);
        }
        i++;
    }    
}
