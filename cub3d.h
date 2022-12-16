#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include "gnl/get_next_line.h"

typedef struct s_vars 
{
    int		i;
	int		tex;
	int		cf;
	char	**tab;
	int		j;
}				t_vars;

typedef struct s_data
{
    int cell;
    int floor;
    char *no;
    char *so;
    char *we;
    char *ea;
    int **map;
    int width;
    int height;
    int x;
    int y;
    enum
    {
        N,
        S,
        E,
        W
    }   e_dir;
}               t_data;

int	    is_digit(char c);
int     str_is_space(char *str);
int     str_is_newline(char *str);
char    *extract_newline(char *str);
char	**ft_split(char const *s, char c);
int	    ft_atoi(const char *str);
int	    ft_int_strrchr(const char *s, int c);
void	errors(int error);
void	ft_putstr_fd(char *s, int fd);
void    print_array(char **array);
char	*remove_spaces(char *colors);

void	check_filename(char *str, int ex);
char    **collect_identifiers(char **file);
int     check_iden(char **tab);
char    **collect_map(char **file);
int     is_mapline(char **file, int i);
int	    is_identifier(char **file, int i);
int	    is_cellingfloor(char **file, int i);

#endif