/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:46:03 by herrakot          #+#    #+#             */
/*   Updated: 2024/11/06 18:00:03 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

t_env *create_node(const char *string) 
{
    t_env *node = NULL;

    node = malloc(sizeof(t_env));
    if (node) 
    {
        node->str = ft_strdup(string);
        node->next = NULL;
    }
    return node;
}

void add_node_end(t_env **head, const char *str)
{
    t_env *new_node = NULL;
    t_env *current  = NULL;

    new_node = malloc(sizeof(t_env));
    new_node->str = strdup(str);
    new_node->next = NULL;

    if (*head == NULL) 
    {
        *head = new_node;
        return;
    }

    current  = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

t_env *create_linked_list(char **str)
{
    t_env *head = NULL;
    t_env *tail = NULL;
    t_env *new_node = NULL;

    while (*str) 
    {
        new_node = create_node(*str++);
        if (!new_node) 
            return (NULL);
        if (!head)
            head = new_node;
        else 
            tail->next = new_node;
        tail = new_node;
    }
    return (head);
}

