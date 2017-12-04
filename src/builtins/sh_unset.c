/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:06:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 16:19:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_unset_opt(char **av, char *opt)
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
			if (av[i][j] == 'f' || av[i][j] == 'v')
			{
				if (*opt && *opt != av[i][j])
					return (0);
				*opt = av[i][j];
			}
			else
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

static int	sh_unset_i(char **av, char *opt)
{
	int		i;

	if ((i = sh_unset_opt(av, opt)) < 0)
	{
		ft_putendl_fd(SH_ILL_OPT("unset", -i), 2);
		ft_putendl_fd(SH_UNSET, 2);
	}
	else if (i == 0)
	{
		ft_error(av[0], "Cannot simultaneously unset"
				"a function and a variable", NULL);
	}
	return (i);
}

int			sh_unset(char **av)
{
	char	opt;
	char	type;
	int		i;
	int		ret[2];

	opt = 0;
	if ((i = sh_unset_i(av, &opt)) <= 0)
		return (1);
	type = (opt == 'f' ? V_FUNCT : 0);
	ret[0] = 0;
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
			ret[0] = 1;
		else if ((ret[1] = sh_unsetvar(av[i], 0, type)) < 0)
			return (-1);
		else if (ret[1] == V_RDONLY)
			ret[0] = ft_error(SHELL, av[i], "Readonly variable");
		i++;
	}
	return (0);
}
