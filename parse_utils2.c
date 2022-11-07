/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 00:41:55 by amoubare          #+#    #+#             */
/*   Updated: 2022/11/07 16:32:38 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	*allocwords(char const *s, char c, int i)
{
	int		j;
	char	*str;

	j = i;
	while (s[j] != c && s[j])
	{
		j++;
	}
	str = malloc(sizeof(char) * j + 1);
	if (str == NULL)
		return (0);
	j = 0;
	while (s[i] && s[i] != c)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (0);
	str = malloc(sizeof(char *) * (countword(s, c) + 1));
	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			str[j] = allocwords(s, c, i);
			j++;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	a;
	long	k;

	k = 0;
	a = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '-' || str[i] == '+') && is_digit(str[i + 1]))
	{
		if (str[i] == '-')
			a = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			errors(6);
		k = k * 10 + str[i] - '0';
		i++;
	}
	return (k * a);
}
