/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rdonly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:59:29 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/17 16:36:45 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_rdy_print(void)
{
	int		i;
	char	***vray;

	if (!(vray = sh_var()))
		return (-1);
	i = 0;
	while ((*vray)[i])
	{
		if ((*vray)[i] & V_RDONLY)
		{
			ft_putstr("readonly ");
			ft_putendl((*vray)[i]);
		}
		i++;
	}
	return (0);
}

static int	sh_rdy_error(char c)
{
	ft_printf("readonly: illegal option -- %c\n", c);
	ft_putendl("usage: readonly [-p] [name=value]...");
	return (1);
}

static int	sh_rdy_opt(char *opt)
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

int			sh_readonly(char **av)
{
	int		i;
	int		opt;

	i = 1;
	if (av[i] && (opt = sh_rdy_opt(av[i])) < 0)
		return (sh_rdy_error(av[i][-opt]));
	else if (!av[1] || opt)
		return (sh_rdy_print());
	else
	{
		while (av[i + 1])
		{
			if ((sh_setvar(av[i], av[i + 1], V_RDONLY)) < 0)
				return (-1);
			i++;
		}
	}
	return (0);
}
