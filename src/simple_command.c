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

/*function to print env because env change with export*/
void print_env(t_env *head)
{
    t_env *current = head;
    while (current != NULL)
    {
        printf("%s%s%s\n", current->var_name, current->sep, current->content);
        current = current->next;
    }
}



/*need the solve by ASCII and the replace function 
for example if there is TEST=1 and we do export TEST=42 we simple replace TEST(need to make unset work first) */
void export_variable(t_env **env_list, char *var_name, char *content)
{
    t_env *current = *env_list;
    // Check if the variable already exists and update it
    while (current)
    {
        if (strcmp(current->var_name, var_name) == 0)
        {
            free(current->content);
            current->content = content ? strdup(content) : NULL;
            return;
        }
        current = current->next;
    }
    // If not found, add a new variable
    t_env *new_var = create_env_node(var_name, content);
    if (new_var)
        append_env_node(env_list, new_var);
}



/* Still need to be fixed so dont touch yet */
/*supposed to remove but is not*/

void unset_variable(t_env **env_list, char *var_name)
{
    t_env *current = *env_list;
    t_env *prev = NULL;
    // Find the variable in the list
    while (current)
    {
        if (strcmp(current->var_name, var_name) == 0)
        {
            // Remove the node
            if (prev)
                prev->next = current->next;
            else
                *env_list = current->next;
            // Free memory
            free(current->var_name);
            free(current->sep);
            free(current->content);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}

/* Still need to be fixed so dont touch yet */
