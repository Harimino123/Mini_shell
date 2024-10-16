/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:45:04 by hrasolof          #+#    #+#             */
/*   Updated: 2024/10/16 17:46:49 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void free_tab(char **str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        free (str[i]);
        i++;
    }
    free (str);
}