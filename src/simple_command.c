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
int print_env(t_env *head)
{
    printf("THE ENV FUNCTION WORKED\n");
    while (head)
    {
        printf("%s\n", head->str);
        head = head->next;
    }
    return (1);
}



/*need the solve by ASCII and the replace function 
for example if there is TEST=1 and we do export TEST=42 we simple replace TEST(need to make unset work first) */
int ft_export(char **av, t_env **head)
{
    if (av[1])
        add_node_end(head, av[1]);
    else
        print_env(*head); // I still need to find a way to show it solved in ASCII way.
    return (1);
}



/* Still need to be fixed so dont touch yet */
/*supposed to remove but is not*/

int unset_env(t_env **head, char *str_to_remove)
{
    t_env *current = NULL;

    current = *head;

    // Traverse the list to find the node to remove
    while (current != NULL)
    {
        if (ft_search_until_egal(str_to_remove, current->str) == 0)
        {
            *head = current->next;
            print_env(*head);
            return (1);            // Exit the function after removing the node
        }
        else
            current = *head;
    current = current->next;
    }
    return (1);
}

/* Still need to be fixed so dont touch yet */
