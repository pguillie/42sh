/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:45:18 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/17 16:54:16 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_exp_print(void)
{
	int		i;
	char	***vray;

	if (!(vray = sh_var()))
		return (-1);
	i = 0;
	while ((*vray)[i])
	{
		if ((*vray)[i] & V_EXPORT)
		{
			ft_putstr("export ");
			ft_putendl((*vray)[i]);
		}
		i++;
	}
	return (0);
}

static int	sh_exp_error(char c)
{
	ft_printf("export: illegal option -- %c\n", c);
	ft_putendl("usage: export [-p] [name=value]...");
	return (1);
}

static int	sh_exp_opt(char *opt)
{
	int		i;

	if (opt[0] != '-')
		return (0);
	i = 1;
	while (opt[i] && opt[i] == 'p')
		i++;
	if (opt[i] && opt[i] != 'p')
		return (-i);
	return (1);
}

int			sh_export(char **av)
{
	int		i;
	int		opt;

	i = 1;
	if (av[i] && (opt = sh_exp_opt(av[i])) < 0)
		return (sh_exp_error(av[i][-opt]));
	else if (!av[1] || opt)
		return (sh_exp_print());
	else
	{
		while (av[i + 1])
		{
			if ((sh_setvar(av[i], av[i + 1], V_EXPORT)) < 0)
				return (-1);
			i++;
		}
	}
	return (0);
}
