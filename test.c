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

#include <stdlib.h>
#include <string.h>

char *remove_quotes(const char *str)
{
    size_t len = strlen(str);

    if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
    {
        char *result = (char *)malloc(len - 1);
        if (!result)
            return NULL;
        strncpy(result, str + 1, len - 2);
        result[len - 2] = '\0';
        return result;
    }
    return strdup(str);
}

#include <stdio.h>

int main()
{
    char *input = "\"test\"";
    char *output = remove_quotes(input);
    printf("Result: %s\n", output);
    free(output); // Free the allocated memory
    return 0;
}


