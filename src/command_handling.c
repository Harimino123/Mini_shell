/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:48:52 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/27 18:43:37 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int built_in_command(char **av,t_env *head)
{
    if (!av[0])
        return (1);
    if (ft_strcmp(av[0], "cd") == 0)
        return (ft_cd(av));
    else if (ft_strcmp(av[0], "exit") == 0)
        return (ft_exit(av));
    else if (ft_strcmp(av[0], "export") == 0) //this part is too long but it will not work without all of this things
    {
        if (av[1])
        {
            char *equal_sign = strchr(av[1], '=');
            char *var_name = NULL;
            char *content = NULL;

            if (equal_sign)
            {
                var_name = strndup(av[1], equal_sign - av[1]);
                content = strdup(equal_sign + 1);
            }
            else
            {
                var_name = strdup(av[1]);
                content = NULL;
            }
            return (export_variable(&head, var_name, content));
        }
        else
            return(print_env(head));
    }
    else if (ft_strcmp(av[0], "env") == 0)
        return (print_env(head));
    else if (ft_strcmp(av[0], "unset") == 0)
        return (unset_variable(&head, av[1]));
    return (0);
}
