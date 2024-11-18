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

/*struct for token function*/
typedef struct  s_datatok
{
    int  index;
    int  index2;
    int  w_len;
    int     tab_i;
    char    **out;
}   t_datatok;

/*struct for path function*/
typedef struct s_dir
{
    char    *path_env;
    char    *dir;
    char    *dir_with_slash;
    char    *full_path;
    char    **dirs;
}   t_dir;

/*struct for env node and stuff*/
typedef struct s_env
{
    char    *var_name;
    char    *sep;
    char    *content;
    struct s_env    *next;
}   t_env;

int ft_cd(char **av);
int ft_exit();
int ft_isspace(char c);
int ft_special_char(char c);
int built_in_command(char **av, t_env *head);
int execute_command(char **args, char **env);
int export_variable(t_env **env_list, char *var_name, char *content);
int unset_variable(t_env **env_list, char *var_name);
int print_env(t_env *head);
int     ft_search_until_egal(char *str, char *str_tocompare);
char	**ft_toksplit(const char *str);
char *find_program_in_path(const char *program);
t_env *create_env_node(char *var_name, char *content);
t_env *create_linked_list(char **str);
void free_tab(char **str);
void free_tab_struct(t_datatok *data);
void append_env_node(t_env **env_list, t_env *new_node);
void free_tab(char **str);
void free_tab_struct(t_datatok *data);
void ft_remove_quote(char   **args);

#endif









