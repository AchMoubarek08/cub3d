/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:31:34 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/17 00:34:47 by amoubare         ###   ########.fr       */
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
	if(ft_int_strchr(file[i], 'C') != -1)
		return (1);
	else if(ft_int_strchr(file[i], 'F') != -1)
		return (2);
	return (0);
}

int	is_identifier(char **file, int i)
{
	if (ft_int_strchr(file[i], 'N') != -1 
		&& ft_int_strchr(file[i], 'O') != -1)
		return (1);
	else if (ft_int_strchr(file[i], 'S') != -1 
		&& ft_int_strchr(file[i], 'O') != -1)
		return (2);
	else if (ft_int_strchr(file[i], 'W') != -1
		&& ft_int_strchr(file[i], 'E') != -1)
		return (3);
	else if (ft_int_strchr(file[i], 'E') != -1
		&& ft_int_strchr(file[i], 'A') != -1)
		return (4);
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
	if(file[i][j] == '\0')
		return (0);
	while(file[i][j])
	{
		if (is_mapchar(file[i][j]))
			j++;
		else
			errors(8);
	}
	return (1);
}
void	skip_identifiers(char **file, int *i)
{
	while(file[*i])
	{
		if (is_cellingfloor(file, *i) || is_identifier(file, *i) || str_is_newline(file[*i]) || str_is_space(file[*i]))
			(*i)++;
		else
			break;
	}
}
int	str_is_nothing(char *str)
{
	if(str[0] == '\0')
		return (1);
	return (0);
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
	skip_identifiers(file, &i);
	while(file[i])
	{
		if(is_mapline(file, i))
		{
			while(file[i] && is_mapline(file, i))
			{
				map[j] = ft_strdup(file[i]);
				i++;
				j++;
			}
		}
		while(file[i])
		{
			printf("%s\n", file[i]);
			if((str_is_space(file[i]) || str_is_newline(file[i])))
				i++;
			else
				errors(8);
		}
	}
	map[j] = NULL;
	return(map);
}
void	init_vars(t_vars *x)
{
	x->i = 0;
	x->j = 0;
	x->tex = 0;
	x->cf = 0;
	x->tab = malloc(sizeof(char *) * 7);
}
int	collect_iden(t_vars *x, char **file)
{
	if (str_is_space(file[x->i]) || str_is_newline(file[x->i]))
	{
		(x->i)++;
		return (1);
	}
	else
	{
		if (is_identifier(file, x->i))
		{
			x->tab[x->j] = file[x->i];
			(x->tex)++;
		}
		else if (ft_int_strchr(file[x->i], ',') != -1)
		{
			x->tab[x->j] = file[x->i];
			(x->cf)++;
		}
		else if(is_mapline(file, x->i))
			return (2);
		else if (!str_is_newline(file[x->i]) && !str_is_space(file[x->i]))
			errors(3);
	}
	(x->j)++;
	(x->i)++;
	return (0);
}
char **collect_identifiers(char **file)
{
	t_vars x;
	init_vars(&x);
    while (file[x.i])
    {
		if(collect_iden(&x, file) == 2)
			break;
    }
	x.tab[x.j] = NULL;
	if (x.tex != 4 || x.cf != 2)
		errors(3);
    return (x.tab);
}
