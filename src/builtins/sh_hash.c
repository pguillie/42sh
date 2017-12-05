/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:47:51 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/05 00:40:48 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hash_opt(char **av, int *opt)
{
	int		i;
	int		j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "-") || (ft_strequ(av[i], "--") && ++i))
			break ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'r')
				*opt = 1;
			else
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

int			sh_hash(char *av[])
{
	int		i;
	int		opt;
	char	*path;

	opt = 0;
	if ((i = sh_hash_opt(av, &opt)) < 0)
		return (sh_ill_opt(av[0], -i, SH_HASH));
	if (opt)
		sh_hash_free();
	else if (!av[i])
		sh_hash_disp();
	while (av[i])
	{
		path = NULL;
		if (!ft_strchr(av[i], '/'))
			if (!sh_hash_get(av[i]) && !sh_exec_bin(av[i], &path))
			{
				sh_hash_set(av[i], path);
				free(path);
			}
		i++;
	}
	return (0);
}
