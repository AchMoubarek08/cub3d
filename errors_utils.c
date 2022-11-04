/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:45:51 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/04 11:54:18 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	errors(int error)
{
	if (error == 1)
		ft_putstr_fd("invalide texture identifier\n", 2);
	else if (error == 2)
		ft_putstr_fd("invalide texture path\n", 2);
	else if (error == 3)
		ft_putstr_fd("wrong number of identifiers\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
