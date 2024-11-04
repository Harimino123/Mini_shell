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
#include <sys/stat.h>
#include "../Libft/libft.h"

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define BOLD "\033[1m"

#define TOKEN_BUFFER_SIZE 64

typedef struct  s_datatok
{
    int  index;
    int  index2;
    int  w_len;
    int     tab_i;
    char    **out;
}   t_datatok;


typedef struct s_dir
{
    char    *path_env;
    char    *dir;
    char    *dir_with_slash;
    char    *full_path;
    char    **dirs;
}   t_dir;
typedef struct s_env
{
    char *str;
    struct s_env *next;
}   t_env;

int ft_cd(char **av);
int ft_exit();
int ft_export(char **av, t_env **head);
int ft_isspace(char c);
int ft_special_char(char c);
int built_in_command(char **av, t_env *head);
int execute_command(char **args, char **env);
char	**ft_toksplit(const char *str);
char *find_program_in_path(const char *program);
void free_tab(char **str);
void free_tab_struct(t_datatok *data);
t_env *create_node(const char *string);
t_env *create_linked_list(char **str);
int print_env(t_env *head);
void add_node_end(t_env **head, const char *string);
int unset_env(t_env **head, char *str_to_remove);
void free_tab(char **str);
void free_tab_struct(t_datatok *data);
void ft_remove_quote(char   **args);
int     ft_search_until_egal(char *str, char *str_tocompare);




#endif









