/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:00:42 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/20 17:30:15 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_declare_opt(char **av, char *opt)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--") && ++i)
			break ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'r')
				opt[1] |= V_RDONLY;
			else if (av[i][j] == 'x')
				opt[1] |= V_EXPORT;
			else if (av[i][j] == 'p')
				opt[0] = 1;
			else
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

static void	sh_declare_print_out(char *var)
{
	int	i;

	ft_putstr("declare ");
	if ((i = 1) && var[0])
	{
		ft_putchar('-');
		var[0] & V_RDONLY ? ft_putchar('r') : 0;
		var[0] & V_EXPORT ? ft_putchar('x') : 0;
		ft_putchar(' ');
	}
	while (var[i] && var[i] != '=')
		i++;
	write(1, var + 1, i - 1);
	if (var[i++])
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

static int	sh_declare_print_name(char **av)
{
	char	***varray;
	int		ret;
	int		i;
	int		j;
	int		l;

	if (!(varray = sh_var()))
		return (1);
	ret = 0;
	i = 0;
	while (av[i])
	{
		l = 0;
		while (av[i][l] && av[i][l] != '=')
			l++;
		j = 0;
		while ((*varray)[j])
		{
			if (ft_strnequ((*varray)[j] + 1, av[i], l)
					&& (*varray)[j][l + 1] == '=')
				break ;
			j++;
		}
		if ((*varray)[j])
			sh_declare_print_out((*varray)[j]);
		else if ((ret = 1))
			ft_error("declare", av[i], "Not found");
		i++;
	}
	return (ret);
}

static int	sh_declare_print_type(int type)
{
	char	***varray;
	int		i;

	if (!(varray = sh_var()))
		return (1);
	i = 0;
	while ((*varray)[i])
	{
		if (!type || (*varray)[i][0] & type)
			sh_declare_print_out((*varray)[i]);
		i++;
	}
	return (0);
}

int			sh_declare(char **av)
{
	char	opt[2];
	int		ret[2];
	int		i;

	ft_printf(">>\n");
	ft_memset(opt, 0, sizeof(char) * 2);
	if ((i = sh_declare_opt(av, opt)) < 0)
	{
		ft_putendl_fd(SH_ILL_OPT("declare", -i), 2);
		ft_putendl_fd(SH_DECLARE, 2);
		return (1);
	}
	ft_printf("opt: %d -- type: %d\n", opt[0], opt[1]);
	if (opt[0] && av[i])
		return (sh_declare_print_name(av + i));
	else if (opt[0])
		return (sh_declare_print_type(opt[1]));
	ret[0] = 0;
	while (av[i])
	{
		if ((ret[1] = sh_setvar(av[i], NULL, opt[1])) < 0)
			return (-1);
		else if (ret[1] > 1)
			ret[0] = ft_error(av[0], av[i], "Not a valid identifier");
		i++;
	}
	return (ret[0]);
}
