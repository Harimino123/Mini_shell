/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:43:17 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/28 14:28:32 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main() {
//     int pipefd[2]; // Pipe file descriptors
//     pid_t pid;

//     if (pipe(pipefd) == -1) { // Create pipe
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid = fork(); // Create a child process

//     if (pid == -1) { // Error in fork
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0) { 
//         // Child process: Runs "grep .c"
//         close(pipefd[1]);               // Close write end
//         dup2(pipefd[0], STDIN_FILENO);  // Redirect read end to stdin
//         close(pipefd[0]);               // Close the original read end
//         execlp("grep", "grep", ".c", NULL); // Execute grep
//         perror("execlp");               // If execlp fails
//         exit(EXIT_FAILURE);
//     } else {
//         // Parent process: Runs "ls"
//         close(pipefd[0]);               // Close read end
//         dup2(pipefd[1], STDOUT_FILENO); // Redirect write end to stdout
//         close(pipefd[1]);               // Close the original write end
//         execlp("ls", "ls", NULL);       // Execute ls
//         perror("execlp");               // If execlp fails
//         exit(EXIT_FAILURE);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main() {
//     int pipefd[2]; // Pipe file descriptors
//     pid_t pid;
//     int numbers[] = {1, 2, 3, 4, 5}; // Numbers to sum
//     int size = sizeof(numbers) / sizeof(numbers[0]);

//     if (pipe(pipefd) == -1) { // Create pipe
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid = fork(); // Create child process

//     if (pid == -1) { // Error in fork
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0) { 
//         // Child process: Calculates the sum
//         close(pipefd[1]); // Close write end
//         int sum = 0, num;

//         // Read numbers from the pipe
//         while (read(pipefd[0], &num, sizeof(int)) > 0) {
//             sum += num;
//         }

//         close(pipefd[0]); // Close read end
//         printf("Sum of numbers: %d\n", sum);
//         exit(EXIT_SUCCESS);
//     } else {
//         // Parent process: Sends numbers
//         close(pipefd[0]); // Close read end

//         // Write numbers to the pipe
//         int i = 0;
//         while (i < size)
//         { 
//             write(pipefd[1], &numbers[i], sizeof(int));
//             i++;
//         }
//         close(pipefd[1]); // Close write end
//         wait(NULL);       // Wait for child to finish
//         exit(EXIT_SUCCESS);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main() {
//     int pipe1[2], pipe2[2]; // Two pipes
//     pid_t pid1, pid2;

//     if (pipe(pipe1) == -1 || pipe(pipe2) == -1) { // Create pipes
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // First child process: runs "ls"
//     pid1 = fork();
//     if (pid1 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid1 == 0) {
//         // Redirect stdout to Pipe 1 write-end
//         dup2(pipe1[1], STDOUT_FILENO);
//         close(pipe1[0]); // Close unused read-end
//         close(pipe1[1]); // Close original write-end
//         close(pipe2[0]); // Close unused pipe 2
//         close(pipe2[1]);
//         execlp("ls", "ls", NULL);
//         perror("execlp ls");
//         exit(EXIT_FAILURE);
//     }

//     // Second child process: runs "grep .c"
//     pid2 = fork();
//     if (pid2 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid2 == 0) {
//         // Redirect stdin to Pipe 1 read-end
//         dup2(pipe1[0], STDIN_FILENO);
//         // Redirect stdout to Pipe 2 write-end
//         dup2(pipe2[1], STDOUT_FILENO);
//         close(pipe1[0]); // Close original read-end
//         close(pipe1[1]); // Close unused write-end
//         close(pipe2[0]); // Close unused read-end
//         close(pipe2[1]); // Close original write-end
//         execlp("grep", "grep", ".c", NULL);
//         perror("execlp grep");
//         exit(EXIT_FAILURE);
//     }

//     // Parent process: runs "wc -l"
//     close(pipe1[0]); // Close unused pipe 1
//     close(pipe1[1]);
//     close(pipe2[1]); // Close write-end of Pipe 2

//     // Redirect stdin to Pipe 2 read-end
//     dup2(pipe2[0], STDIN_FILENO);
//     close(pipe2[0]); // Close original read-end
//     execlp("wc", "wc", "-l", NULL);
//     perror("execlp wc");
//     exit(EXIT_FAILURE);

//     return 0;
// }

/*EAMPLE OF DYNAMIC PIPELINE BELOW*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10 // Maximum number of commands in the pipeline
#define MAX_ARGS 100    // Maximum number of arguments per command

void parse_command(char *input, char *commands[])
{
    int i = 0;
    char *token = strtok(input, "|");
    while (token != NULL && i < MAX_COMMANDS)
    {
        commands[i++] = token;
        token = strtok(NULL, "|");
    }
    commands[i] = NULL; // NULL-terminate the array
}

void execute_pipeline(char *commands[])
{
    int num_cmds = 0;
    while (commands[num_cmds] != NULL) num_cmds++;

    int pipefds[2 * (num_cmds - 1)];
    for (int i = 0; i < num_cmds - 1; i++)
    {
        if (pipe(pipefds + i * 2) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_cmds; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Child process
            // Redirect input
            if (i > 0)
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            // Redirect output
            if (i < num_cmds - 1)
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO);

            // Close all pipe fds in child
            for (int j = 0; j < 2 * (num_cmds - 1); j++)
                close(pipefds[j]);

            // Execute command
            char *args[MAX_ARGS];
            char *token = strtok(commands[i], " ");
            int k = 0;
            while (token != NULL && k < MAX_ARGS)
            {
                args[k++] = token;
                token = strtok(NULL, " ");
            }
            args[k] = NULL; // NULL-terminate args

            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Close all pipe fds in parent
    for (int i = 0; i < 2 * (num_cmds - 1); i++)
        close(pipefds[i]);

    // Wait for all child processes to finish
    for (int i = 0; i < num_cmds; i++)
        wait(NULL);
}

int main() {
    char input[1024];
    printf("Enter a pipeline command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

    char *commands[MAX_COMMANDS];
    parse_command(input, commands);
    execute_pipeline(commands);

    return 0;
}
