/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:21:25 by hrasolof          #+#    #+#             */
/*   Updated: 2024/10/16 17:49:59 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int execute_command(char **args, char **env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execve (find_program_in_path(args[0]), args, env) == -1)
        {
            perror ("minishell");
            exit (EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror ("Fork failed");
        return (-1);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}