/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:39:03 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/28 11:53:32 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Libft/libft.h"

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define BOLD "\033[1m"

#define TOKEN_BUFFER_SIZE 64

typedef struct s_dir
{
    char    *path_env;
    char    *dir;
    char    *dir_with_slash;
    char    *full_path;
    char    **dirs;
}   t_dir;

int ft_cd(char **av);
int ft_echo(char **av);
int ft_pwd();
int ft_exit();
// char **tokenize_input(char *input);
int built_in_command(char **av);
char	**ft_toksplit(const char *str);


#endif