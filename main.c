/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:50:18 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/10 11:43:41 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_filename(char *str, int ex)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			break ;
		i++;
	}
    if (ex == 1)
    {
	    if (strcmp(str + i, ".cub") != 0)
        {
	        errors(5);
        }
    }
    else if (ex == 2)
    {
        if (strcmp(str + i, ".xpm") != 0)
        {
            errors(5);
        }
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    int i;
    int fd;

    i = 0;
    if (argv[1])
        check_filename(argv[1], 1);
    fd = open(argv[1], O_RDONLY);
    char *line = get_next_line(fd);
    char **file = malloc(sizeof(char *) * 100);
    while(line)
    {
        line = extract_newline(line);
        file[i] = line;
        line = get_next_line(fd);
        i++;
    }
    file = collect_identifiers(file);
    check_iden(file);
    return (0);
}