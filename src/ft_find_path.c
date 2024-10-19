/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:41:44 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/28 14:55:03 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int is_executable(const char *path)
{
    struct stat buf;

    if (stat(path, &buf) == 0 && (buf.st_mode & S_IXUSR))
        return (1);
    return (0);
}

char *find_program_in_path(const char *program)
{
    t_dir dir_data;

    if (is_executable(program))
        return ((char *)program);
    dir_data.path_env = getenv("PATH");
    if (!dir_data.path_env)
    {
        printf("PATH environment variable not found\n");
        return (NULL);
    }
    dir_data.dirs = ft_split(dir_data.path_env, ':');
    if (!dir_data.dirs)
        return (NULL);
    int i = -1;
    while (dir_data.dirs[++i] != NULL)
    {
        dir_data.dir = dir_data.dirs[i];
        dir_data.dir_with_slash = ft_strjoin(dir_data.dir, "/");
        dir_data.full_path = ft_strjoin(dir_data.dir_with_slash, program);
        if (is_executable(dir_data.full_path))
            return (dir_data.full_path);
        free(dir_data.full_path);
    }
    return (NULL);
}
