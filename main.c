/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:50:18 by amoubare          #+#    #+#             */
/*   Updated: 2022/10/31 00:07:05 by amoubare         ###   ########.fr       */
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
int parse_identifiens(char **file)
{
    int i;

    i = 0;
    while(file[i])
    {
        if (str_is_space(file[i]) || str_is_newline(file[i]))
        {
            i++;
            continue;
        }
        else
        {
            printf("%s\n", file[i]);
            if(ft_int_strchr(file[i], 'N') != -1
                || ft_int_strchr(file[i], 'S') != -1
                || ft_int_strchr(file[i], 'W' ) != -1
                || ft_int_strchr(file[i], 'E') != -1)
            {
                printf("found texture\n");
            }
            else if(ft_int_strchr(file[i], ',') != -1)
                printf("found C or F\n");
            else if(ft_int_strchr(file[i], '1') != -1)
            {
                printf("found mapline\n");
            }
            else
            {
                printf("error\n");
                return(1);
            }
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    int fd;
    fd = open(argv[1], O_RDONLY);
    int i;

    i = 0;
    char *line = get_next_line(fd);
    char **file = malloc(sizeof(char *) * 100);
    while(line)
    {
        line = extract_newline(line);
        file[i] = line;
        line = get_next_line(fd);
        i++;
    }
    parse_identifiens(file);
    return (0);
}