/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:31:34 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/23 23:55:37 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_txt_path(char *path)
{
	int		i;
	int		j;
	int		fd;
	char	*filename;

	i = ft_int_strchr(path, '.');
	j = ft_int_strrchr(path, 'm');
	if (j == -1)
		errors(5);
	if(i == -1 || (path[i + 1] && path[i + 1] != '/'))
		errors(2);
	filename = ft_substr(path, i, j - i + 1);
	check_filename(filename + 2, 2);
	fd = open(filename + 2, O_RDONLY);
	if(fd == -1)
		errors(4);
	return(0);
}
char	*remove_spaces(char *colors)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while(colors[i] && colors[i] == 32)
		i++;
	while(colors[i] && colors[i] != 32)
	{
		colors[j] = colors[i];
		j++;
		i++;
	}
	while(colors[i])
	{
		if (colors[i] != 32)
			errors(7);
		i++;
	}
	colors[j] = '\0';
	return(0);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int in_range(char *str)
{
	int numb;
	numb = ft_atoi(str);
	if (numb >= 0 && numb <= 255)
		return(0);
	return(1);
}

int	check_cf_colors(char *str)
{
	char	**colors;
	int		i;

	colors = ft_split(str, ',');
	i = 0;
	while(colors[i])
	{
		remove_spaces(colors[i]);
		i++;
	}
	i = 0;
	while(colors[i])
	{
		if (!str_is_digit(colors[i]) && !in_range(colors[i]))
			errors(6);
		i++;
	}
	return(0);
}
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
            check_txt_path(ft_substr(tab[i], 2, ft_strlen(tab[i])));
        }
        else if (tab[i][j] == 'F' || tab[i][j] == 'C')
			check_cf_colors(ft_substr(tab[i], 1, ft_strlen(tab[i])));
        else
            errors(1);
		i++;
	}
    return (0);
}

int	is_cellingfloor(char **file, int i)
{
	if(ft_int_strchr(file[i], 'F') != -1 || ft_int_strchr(file[i], 'C') != -1)
		return (1);
	return (0);
}

int	is_identifier(char **file, int i)
{
	if (ft_int_strchr(file[i], 'N') != -1 
		&& ft_int_strchr(file[i], 'O') != -1)
		return (1);
	else if (ft_int_strchr(file[i], 'S') != -1 
		&& ft_int_strchr(file[i], 'O') != -1)
		return (1);
	else if (ft_int_strchr(file[i], 'W') != -1
		&& ft_int_strchr(file[i], 'E') != -1)
		return (1);
	else if (ft_int_strchr(file[i], 'E') != -1
		&& ft_int_strchr(file[i], 'A') != -1)
		return (1);
	return(0);
}
int	is_mapchar(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ')
		return (1);
	return (0);
}

int	is_mapline(char **file, int i)
{
	int j;
	j = 0;
	while(file[i][j])
	{
		if (is_mapchar(file[i][j]))
			j++;
		else
			return (0);
	}
	return (1);
}

char **collect_map(char **file)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	while(file[i])
		i++;
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(file[i])
	{
		if (is_cellingfloor(file, i) || is_identifier(file, i) || str_is_newline(file[i]) || str_is_space(file[i]))
			i++;
		else
			break;
	}
	while(file[i])
	{
		while (!is_mapline(file, i))
			i++;
		while(file[i])
		{
			map[j] = ft_strdup(file[i]);
			i++;
			j++;
		}
	}
	map[j] = NULL;
	return(map);
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
	tab = malloc(sizeof(char *) * 7);
    while (file[i])
    {
        if (str_is_space(file[i]) || str_is_newline(file[i]))
        {
            i++;
            continue;
        }
        else
        {
            if (is_identifier(file, i))
            {
				tab[j] = file[i];
                tex++;
            }
            else if (ft_int_strchr(file[i], ',') != -1)
			{
				tab[j] = file[i];
                cf++;
			}
			else if(is_mapline(file, i))
				break;
			else if (!str_is_newline(file[i]) && !str_is_space(file[i]))
				errors(3);
        }
		j++;
        i++;
    }
	if (tex != 4 || cf != 2)
		errors(3);
	tab[j] = NULL;
    return (tab);
}
