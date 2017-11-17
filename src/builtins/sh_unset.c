/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:06:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/17 16:34:32 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"

static int	sh_unset_error(char c, int err_type)
{
	if (err_type == 1)
	{
		ft_printf("unset: illegal option -- %c\n", c);
		ft_printf("usage: unset [-f] [-v] [name ...]\n");
	}
	else
		ft_printf("unset: Cannot simultaneously"
				" unset a function and a variable.\n");
	return (-1);
}

static int	sh_unset_opt(char **av, int *opt)
{
	int		i;
	int		j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--"))
			break ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'f' || av[i][j] == 'v')
			{
				if (*opt && *opt != av[i][j])
					return (sh_unset_error(0, 2));
				*opt = av[i][j];
			}
			else
				return (sh_unset_error(av[i][j], 1));
			j++;
		}
		i++;
	}
	return (i);
}

int			sh_unset(char **av)
{
	int		i;
	int		opt;

	opt = 0;
	if ((i = sh_unset_opt(av, &opt)) < 0)
		return (i);
	if (!av[i])
		return (0);
	while (av[i])
	{
		if (opt == 'f')
			sh_unsetvar(av[i], NULL);
		else if (opt == 'v')
			sh_unsetvar(av[i], NULL);
		i++;
	}
	return (0);
}
