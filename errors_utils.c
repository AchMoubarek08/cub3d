/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:45:51 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/29 01:11:25 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	errors(int error)
{
	if (error == 1)
		ft_putstr_fd("indetifien(s) de texture invalide(s)\n", 2);
	else if (error == 2)
		ft_putstr_fd("Chemin(s) de texture invalide(s)\n", 2);
	else if (error == 3)
		ft_putstr_fd("Nombre d'indentifiens invalide\n", 2);
	else if (error == 4)
		ft_putstr_fd("fichier(s) de texture incorrect\n", 2);
	else if (error == 5)
		ft_putstr_fd("Extension de fichier invalide\n", 2);
	else if (error == 6)
		ft_putstr_fd("Couleur(s) RGB hors intervalle\n", 2);
	else if (error == 7)
		ft_putstr_fd("Couleur(s) RGB invalide\n", 2);
	else if (error == 8)
		ft_putstr_fd("Map invalide\n", 2);
	else if (error == 9)
		ft_putstr_fd("Map non fermée\n", 2);
	else if (error == 10)
		ft_putstr_fd("More or less than one player\n", 2);
	else if (error == 11)
		ft_putstr_fd("More than one argument\n", 2);
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
