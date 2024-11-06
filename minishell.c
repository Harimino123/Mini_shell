/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:39:06 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/27 18:43:28 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int ac, char *av[], char **env)
{   
    (void)ac;
    (void)av;
    char    *input;
    char    **args = NULL;
    t_env   *envp = NULL;
    (void)envp;

    /*store the entire env in a linked list to manipulate it more easily*/
    envp = create_linked_list(env);
    /* IDEA = 1st create a function that check the position of the 1st "="
    then store the value before it to "var_name" in the struct and the 
    "=" in the "sep" and finally store the remaining in the "content" 
    variable. "Next" will point to the next node of course. In this way, 
    i think it will more easy to create and change variable env and to 
    delete it*/

    while (1)
    {
        input = readline("\033[1mMinishell \U0001F60A $\033[0m ");
        if (!input)
            break ;
        if (*input)
            add_history(input);
        args = ft_toksplit(input);
        if (!built_in_command(args, envp))
            execute_command(args, env);
        free(input);
        free_tab(args);
    }
}
