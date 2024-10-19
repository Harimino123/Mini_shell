/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:15:50 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/26 10:24:40 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int ft_cd(char **av)
{
    const char *home;

    if (av[1] == NULL)
    {
        home = getenv("HOME");
        if (home == NULL)
        {
            printf("minishell : cd : HOME not found");
            return (0);
        }
        if (chdir(home) != 0)
        {
            perror("minishell");
            return (0);
        }
    }
    else
    {
        if (chdir(av[1]) != 0)
            perror("minishell");
    }
    return (1);
}

int ft_exit()
{
    printf("exit\n");
    exit(0);
    return (0);
}
