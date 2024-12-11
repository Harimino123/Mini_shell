/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_function.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:04:54 by hrasolof          #+#    #+#             */
/*   Updated: 2024/12/11 11:11:39 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/minishell.h"

/*ONLY DRAFT, NOT THE REAL ONE FOR NOW*/

void execute_pipeline(char **args, t_env *envp)
{
    (void)envp;
    int i = 0;
    int pipefd[2];
    pid_t pid;
    int prev_fd = 0;  // Tracks the previous pipe's read end

    // Iterate through the commands separated by pipes
    while (args[i] != NULL) {
        // Set up a pipe only if this isn't the last command in the pipeline
        if (args[i + 1] != NULL) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            // Redirect the input from the previous command's output
            if (prev_fd != 0) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // If this is not the last command, redirect output to the pipe
            if (args[i + 1] != NULL) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            // Execute the current command
            if (execvp(args[i], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {  // Parent process
            // Close the write end of the pipe (in parent)
            if (args[i + 1] != NULL) {
                close(pipefd[1]);
            }

            // Save the read end of the current pipe for the next iteration
            prev_fd = pipefd[0];

            // Wait for the child process to finish (we'll wait for the last one later)
            waitpid(pid, NULL, 0);
        }

        // Move to the next command in the pipeline
        i++;
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);
}
