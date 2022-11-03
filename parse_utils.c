/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:32:42 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/03 22:32:57 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *extract_newline(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\n' && str[i] != '\0')
        i++;
    str[i++] = '\0';
    return(ft_substr(str, 0, i));
}
void    print_array(char **array)
{
    int i;

    i = 0;
    while(array[i])
    {
        printf("%s\n", array[i]);
        i++;
    }
}
int str_is_space(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}
int str_is_newline(char *str)
{
    int i;

    i = 0;
    if(str[i] == '\n')
        return(1);
    return(0);
}