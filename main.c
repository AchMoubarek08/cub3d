/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:50:18 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/17 00:15:40 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_filename(char *str, int ex)
{
	int	i;
    int fd;

    fd = open(str, O_RDONLY);
    if(fd == -1)
        errors(5);
	i = 0;
    if (!strcmp(str + i, ".cub") || !strcmp(str + i, ".xpm"))
	        errors(2);
	while (str[i])
	{
		if (str[i] == '.')
			break ;
		i++;
	}
    if (ex == 1)
    {
	    if (strcmp(str + i, ".cub") != 0)
	        errors(5);
    }
    else if (ex == 2)
    {
        if (strcmp(str + i, ".xpm") != 0)
            errors(5);
    }
}

int	check_closed(char **map, int i)
{
    int j;

    j = 0;
    if(!map[i + 1])
        errors(9);
    while(map[i][j])
    {
        if(map[i][j] == '0')
        {
            if (!map[i][j + 1] || !map[i][j - 1])
                errors(9);
            else if(map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
                errors(9);
            if(!map[i - 1][j] || !map[i + 1][j])
                errors(9);
            else if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
                errors(9);
        }
        j++;
    }
    return (0);
}

int check_first_line(char *map)
{
    int i;

    i = 0;
    while (map[i])
    {
        if (map[i] == '0')
            errors(9);
        i++;
    }
    return(0);
}
int there_is_zero(char **map, int i)
{
    int j;

    j = 0;
    while (map[i][j])
    {
        if (map[i][j] == '0')
            return (1);
        j++;
    }
    return (0);
}

int check_upcoming_lines(char **map, int i)
{
    i++;
    while(map[i])
    {
        if(strcmp(map[i], ""))
            errors(8);
        i++;
    }
    return (0);

}
int check_map(char **map)
{
    int i;

    i = 0;
    while(map[i])
    {
        if(strcmp(map[i], "") == 0)
            check_upcoming_lines(map, i);
        if(!is_mapline(map, i))
            errors(8);
        if(i == 0)
            check_first_line(map[i]);
        else if(there_is_zero(map, i))
            check_closed(map, i);
        i++;
    }
    return (0);
}
void    fill_cf_colors(t_data *data, char *line, int x)
{
    char **colors;
    int i;
    int r;
    int g;
    int b;

    colors = ft_split(line, ',');
    i = 0;
    while(colors[i])
    {
        remove_spaces(colors[i]);
        i++;
    }
    r = ft_atoi(colors[0]);
    g = ft_atoi(colors[1]);
    b = ft_atoi(colors[2]);
    if(x == 1)
        data->cell = (r << 16) + (g << 8) + b;
    else if(x == 2)
        data->floor = (r << 16) + (g << 8) + b;
}
void    fill_iden(t_data *data, char **file)
{
    int i;
    int start;
    int end;

    i = 0;
    while (file[i])
    {
        start = ft_int_strchr(file[i], '.');
        end = ft_int_strrchr(file[i], 'm');
        if (is_identifier(file, i) == 1)
            data->no = ft_substr(file[i], start, end - start + 1);
        else if (is_identifier(file, i) == 2)
            data->so = ft_substr(file[i], start, end - start + 1);
        else if (is_identifier(file, i) ==  3)
            data->we = ft_substr(file[i], start, end - start + 1);
        else if(is_identifier(file, i) == 4)
            data->ea = ft_substr(file[i], start, end - start + 1);
        else if(is_cellingfloor(file, i) == 1)
            fill_cf_colors(data, file[i] + 1, 1);
        else if(is_cellingfloor(file, i) == 2)
            fill_cf_colors(data, file [i] + 1, 2);
        i++;   
    }
}

void    get_height_width(t_data *data, char **map)
{
    int i;

    i = 0;
    while(map[i] && is_mapline(map, i) && strcmp(map[i], ""))
    {
        if (ft_strlen(map[i]) > data->width)
            data->width = ft_strlen(map[i]);
        i++;
    }
    data->height = i;
}
void    print_int_tab(int **tab, int width, int height)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            printf("%d", tab[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int fill_tab(t_data *data, char **map, int i, int *j)
{
    static int p;

    if (map[i][*j] == '0')
        data->map[i][*j] = 0;
    else if (map[i][*j] == '1')
        data->map[i][*j] = 1;
    else if (map[i][*j] == ' ')
        data->map[i][*j] = 2;
    else
    {
        p++;
        data->x = *j;
        data->y = i;
        if (map[i][*j] == 'N')
            data->map[i][*j] = 3;
        else if (map[i][*j] == 'S')
            data->map[i][*j] = 4;
        else if (map[i][*j] == 'E')
            data->map[i][*j] = 5;
        else if (map[i][*j] == 'W')
            data->map[i][*j] = 6;
        data->e_dir = data->map[i][*j] - 3;
        data->map[i][*j] = 0;
    }
    (*j)++;
    return(p);
}
void    fill_map(t_data *data, char **map)
{
    int i;
    int j;
    int p;

    i = 0;
    p = 0;
    get_height_width(data, map);
    data->map = malloc(sizeof(int *) * (data->height + 1));
    while(map[i] && is_mapline(map, i))
    {
        
        data->map[i] = malloc(sizeof(int) * (data->width + 1));
        j = 0;
        while(map[i][j])
        {
            
            p = fill_tab(data, map, i, &j);
        }
        while(j < data->width)
        {
            data->map[i][j] = 2;
            j++;
        }
        i++;
    }
    data->map[i] = NULL;
    if(p != 1)
        errors(10);
}
void    print_data(t_data data)
{
    printf("NO texture : %s\n", data.no);
    printf("SO texture : %s\n", data.so);
    printf("WE texture : %s\n", data.we);
    printf("EA texture : %s\n", data.ea);
    printf("X_Pos      : %d\n", data.x);
    printf("Y_Pos      : %d\n", data.y);
    printf("E_DIR      : %d\n", data.e_dir);
    printf("Ceil color : %d\n", data.cell);
    printf("Floor color: %d\n", data.floor);
    printf("Map width  : %d\n", data.width);
    printf("Map height : %d\n", data.height);
    print_int_tab(data.map, data.width, data.height);
}
void    fill_file(char **file, char **av)
{
    int i;
    int fd;
    char *line;

    i = 0;
    fd = open(av[1], O_RDONLY);
    line = get_next_line(fd);
    while(line)
    {
        line = extract_newline(line);
        file[i] = line;
        line = get_next_line(fd);
        i++;
    }
    file[i] = NULL;
}
int main(int argc, char **argv)
{
    (void)argc;
    t_data data;
    char **file;
    char **map;
    if(argc != 2)
        errors(11);
    if (argv[1])
        check_filename(argv[1], 1);
    file = malloc(sizeof(char *) * 100);
    fill_file(file, argv);
    map = file;
    file = collect_identifiers(file);
    check_iden(file);
    map = collect_map(map);
    check_map(map);
    fill_iden(&data, file);
    fill_map(&data, map);
    print_data(data);
    return (0);
}
