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

#include "headers/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the environment variable struct
typedef struct s_env {
    char *var_name;
    char *sep;
    char *content;
    struct s_env *next;
} t_env;

// Helper function to create a new environment variable node
t_env *create_env_node(char *var_name, char *content)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->var_name = strdup(var_name);
    new_node->sep = strdup("=");
    // Handle content allocation
    if (content != NULL)
        new_node->content = strdup(content);
    else
        new_node->content = NULL;
    new_node->next = NULL;
    return (new_node);
}

// Helper function to append a node to the environment list
void append_env_node(t_env **env_list, t_env *new_node)
{
    if (!*env_list)
        *env_list = new_node;
    else
    {
        t_env *current = *env_list;
        while (current->next) current = current->next;
        current->next = new_node;
    }
}

// Function to print all environment variables
void print_env(t_env *env_list)
{
    t_env *current = env_list;
    while (current)
    {
        if (current->content != NULL)
            printf("%s%s%s\n", current->var_name, current->sep, current->content);
        else
            printf("%s%s\n", current->var_name, current->sep);
        current = current->next;
    }
}

// Function to handle the "export" command
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
    if (new_var) append_env_node(env_list, new_var);
}

// Function to handle the "unset" command
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

// Function to initialize the environment list with a sample variable (optional)
t_env *init_env(char **envp)
{
    t_env *env_list = NULL;
    int i = -1;
    while (envp[++i])
    {
        char *equal_sign = strchr(envp[i], '=');
        if (equal_sign)
        {
            char *var_name = strndup(envp[i], equal_sign - envp[i]);
            char *content = strdup(equal_sign + 1);
            t_env *new_var = create_env_node(var_name, content);
            append_env_node(&env_list, new_var);
            free(var_name);
            free(content);
        }
    }
    return (env_list);
}




