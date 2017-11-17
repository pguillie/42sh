/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:00:42 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/17 16:55:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_declare_usage(char opt)
{
	ft_putstr("declare: illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	ft_putendl("usage: declare [-rx] [-p] [name[=value] ...]");
	return (-1);
}

static void	sh_declare_print(int type)
{
	char	***varray;
	int		i;

	if ((varray = sh_var()))
	{
		i = 0;
		while ((*varray)[i])
		{
			if ((*varray)[i] & type)
			{
				ft_putstr("declare ");
				if ((*varray)[i][0])
				{
					ft_putchar('-');
					(*varray)[i][0] & V_RDONLY ? ft_putchar('r') : 0;
					(*varray)[i][0] & V_EXPORT ? ft_putchar('x') : 0;
					ft_putchar(' ');
				}
				sh_varprint((*varray)[i])
			}
			i += 1;
		}
	}
}

static int	sh_declare_opt(char **av, char *opt)
{
	int		i;
	int		j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--"))
			break ;
		while (av[i][j])
		{
			if (av[i][j] == 'p')
				opt[0] = 'p';
			else if (av[i][j] == 'r')
				opt[1] = 'r';
			else if (av[i][j] == 'x')
				opt[2] = 'x';
			else
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

int			sh_declare(char **av)
{
	char	*name;
	char	*value;
	char	opt[3];
	int		type;
	int		i;

	i = 0;
	if ((i = sh_declare_opt(av, opt)) < 0)
		return (sh_declare_usage(-i));
	if (ft_strchr(opt, 'p'))
		;
	while (av[i])
	{
		name = av[i];
		value = ft_strchr(av[i], '=');
		value ? value++ : 0;
		sh_setvar(name, value, opt);
		i++;
	}
}

int			sh_declare(char **av)
{
	char	*name;
	char	*value;
	int		type;
	int		i;
	
	i = 0;
	/* opt */type = 0;
	while (av[i])
	{
		name = av[i];
		value = ft_strchr(av[i], '=');
		value ? value[0] = 0 : 0;
		if (sh_setvar(name, value ? value + 1 : value, type))
			return (-1);
		value ? value[0] = '=' : 0;
		i++;
	}
}
