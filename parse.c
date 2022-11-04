/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:31:34 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/04 11:57:52 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <ctype.h>

int	check_iden(char **tab)
{
	int	i;
    int j;

    i = 0;
	while(tab[i])
	{
        j = 0;
        if ((tab[i][j] == 'N' && tab[i][j + 1] == 'O') 
            || (tab[i][j] == 'S' && tab[i][j + 1] == 'O')
            || (tab[i][j] == 'W' && tab[i][j + 1] == 'E')
            || (tab[i][j] == 'E' && tab[i][j + 1] == 'A'))
        {
                j += 2;
        }
        else if (tab[i][j] == 'F' || tab[i][j] == 'C')
            j++;
        else
            errors(1);
        while(tab[i][j] == 32)
            j++;
        if ((tab[i][j] == '.' && tab[i][j + 1] == '/' )|| isdigit(tab[i][j]))
            j += 2;
        else
            errors(2);
        i++;
	}
    return (0);
}
char **collect_identifiers(char **file)
{
	int		i;
	int		tex;
	int		cf;
	char	**tab;
	int		j;

    i = 0;
	j = 0;
	tex = 0;
	cf = 0;
	tab = malloc(sizeof(char *) * 1000);
    while(file[i])
    {
        if (str_is_space(file[i]) || str_is_newline(file[i]))
        {
            i++;
            continue;
        }
        else
        {
            if(ft_int_strchr(file[i], 'N') != -1
                || ft_int_strchr(file[i], 'S') != -1
                || ft_int_strchr(file[i], 'W' ) != -1
                || ft_int_strchr(file[i], 'E') != -1)
            {
				tab[j] = file[i];
                tex++;
            }
            else if(ft_int_strchr(file[i], ',') != -1)
			{
				tab[j] = file[i];
                cf++;
			}
        }
		j++;
        i++;
    }
	if(cf + tex != 6)
		errors(3);
	tab[j] = NULL;
    return(tab);
}
