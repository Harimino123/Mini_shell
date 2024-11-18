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

/*work as expected but need more test*/
int print_env(t_env *head)
{
    t_env *current = head;
    while (current != NULL)
    {
        printf("%s%s%s\n", current->var_name, current->sep, current->content);
        // printf("<TEST>\n");
        current = current->next;
    }
    return (1);
}



/*this function work as expected but need more test to see 
if there is some issue somewhere*/
int export_variable(t_env **env_list, char *var_name, char *content)
{
    t_env *current = *env_list;

    // Check if the variable already exists and update it
    while (current)
    {
        if (strcmp(current->var_name, var_name) == 0)
        {
            free(current->content);
            current->content = content ? strdup(content) : NULL;
            if (content && !current->content) // strdup failed
                return (0);
            return (1); // Successfully updated
        }
        current = current->next;
    }
    // If not found, add a new variable
    t_env *new_var = create_env_node(var_name, content);
    if (new_var)
    {
        append_env_node(env_list, new_var);
        return (1); // Successfully added
    }
    return (0); // Memory allocation failed
}


/*it remove the variable but need to figure out where is the leaks,
we need to implement a logic to handle case where the variable is not
found instead of returning only (0)*/
int unset_variable(t_env **env_list, char *var_name)
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
            return (1); // Successfully removed
        }
        prev = current;
        current = current->next;
    }
    return (0); // Variable not found
}


/* Still need to be fixed so dont touch yet */
