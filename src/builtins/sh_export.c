/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:45:18 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/20 15:48:25 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_export_opt(char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--") && ++i)
			break ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] != 'p')
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

static void	sh_export_print_out(char *var)
{
	int		i;

	ft_putstr("export ");
	i = 1;
	while (var[i] && var[i] != '=')
		i++;
	write(1, var + 1, i - 1);
	if (var[i])
	{
		ft_putstr("=\"");
		while (var[i])
		{
			if (var[i] == '\\' || var[i] == '\"')
				ft_putchar('\\');
			ft_putchar(var[i++]);
		}
		ft_putchar('\"');
	}
	ft_putchar('\n');
}

static int	sh_export_print(void)
{
	char	***varray;
	int		i;

	if (!(varray = sh_var()))
		return (1);
	i = 0;
	while ((*varray)[i])
	{
		if ((*varray)[i][0] & V_EXPORT)
			sh_export_print_out((*varray)[i]);
		i++;
	}
	return (0);
}

int			sh_export(char **av)
{
	int		ret[2];
	int		i;

	if ((i = sh_export_opt(av)) < 0)
	{
		ft_putendl_fd(SH_ILL_OPT("export", -i), 2);
		ft_putendl_fd(SH_EXPORT, 2);
		return (1);
	}
	ret[0] = 0;
	if (!av[i])
		return (sh_export_print());
	else
	{
		while (av[i])
		{
			if ((ret[1] = sh_setvar(av[i], NULL, V_EXPORT)) < 0)
				return (-1);
			else if (ret[1] && (ret[0] = 1))
				ft_error(av[0], av[i], "Not a valid identifier");
			i++;
		}
	}
	return (ret[0]);
}
