#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include "gnl/get_next_line.h"

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

void	check_filename(char *str, int ex);
char    **collect_identifiers(char **file);
int     check_iden(char **tab);
char    **collect_map(char **file);

#endif