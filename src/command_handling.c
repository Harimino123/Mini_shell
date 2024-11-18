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
    else if (ft_strcmp(av[0], "export") == 0)
    {
        if (av[1])
        { // Ensure there's a second argument (variable to export)
            char *equal_sign = strchr(av[1], '=');
            char *var_name = NULL;
            char *content = NULL;

            if (equal_sign)
            {
                // Split var_name and content
                var_name = strndup(av[1], equal_sign - av[1]);
                content = strdup(equal_sign + 1);
            }
            else
            {
                // Only var_name provided, no content
                var_name = strdup(av[1]);
                content = NULL;
            }
            // Call export_variable and check return value
            if (export_variable(&head, var_name, content))
                printf("Exported: %s=%s\n", var_name, content ? content : "");
            else
                printf("Error: Failed to export variable\n");
            // Free temporary strings
            free(var_name);
            free(content);
        }
        else
        {
            // Handle case where no argument is passed to export
            printf("export: usage: export VAR=value\n");
        }
    }
    else if (ft_strcmp(av[0], "env") == 0)
        return (print_env(head));
    else if (ft_strcmp(av[0], "unset") == 0)
        return (unset_variable(&head, av[1]));
    return (0);
}
