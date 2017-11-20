/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_allwhite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:37:43 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/17 13:32:06 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_white(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static char	**ft_exit(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
	free(tab);
	tab = NULL;
	return (NULL);
}

static int	ft_size(const char *str)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (str[i] && ft_white(str[i]))
		i++;
	while (str[i])
	{
		if (ft_white(str[i]) && str[i + 1] && !ft_white(str[i + 1]))
			n++;
		i++;
	}
	return (n + 2);
}

char		**ft_split_allwhite(char const *str)
{
	char	**new;
	int		i;
	int		j;
	int		l;

	if (!str || !(new = (char**)malloc(sizeof(char*) * ft_size(str))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && ft_white(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] != ' ' && !ft_white(str[i])
			&& (i ? ft_white(str[i - 1]) : 1) && !(l = 0))
		{
			while (str[i + l] && !ft_white(str[i + l]))
				l++;
			if (!(new[j++] = ft_strsub(str, i, l)))
				return (ft_exit(new));
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}
