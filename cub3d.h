#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include "gnl/get_next_line.h"

int     check_iden(char **tab);
char    **collect_identifiers(char **file);
char    *extract_newline(char *str);
void    print_array(char **array);
int     str_is_space(char *str);
int     str_is_newline(char *str);
void	errors(int error);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int	    ft_atoi(const char *str);
int	    is_digit(char c);

#endif