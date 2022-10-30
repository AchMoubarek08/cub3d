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
    return (ft_substr(str, 0, i));
}
int main(int argc, char **argv)
{
    int fd;
    fd = open(argv[1], O_RDONLY);
    char *line = get_next_line(fd);
    while(line)
    {
        line = extract_newline(line);
        printf("%s\n", line);
        line = get_next_line(fd);
    }
}