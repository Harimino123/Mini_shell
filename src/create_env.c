/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:46:03 by herrakot          #+#    #+#             */
/*   Updated: 2024/11/18 09:14:57 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

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

t_env *create_linked_list(char **envp)
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
