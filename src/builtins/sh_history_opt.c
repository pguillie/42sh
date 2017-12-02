/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:50:02 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 21:48:47 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hist_usage(void)
{
	ft_putendl_fd("usage: history [n]", 2);
	ft_putendl_fd("       history -c", 2);
	ft_putendl_fd("       history -d offset", 2);
	ft_putendl_fd("       history -rw [filename]", 2);
	ft_putendl_fd("       history -s arg ...", 2);
	return (-1);
}

static void	sh_hist_opt_add(char *opt, char add)
{
	int	i;

	i = 0;
	while (opt[i])
	{
		if (opt[i++] == add)
			break ;
	}
	if (!opt[i])
		opt[i] = add;
}

static int	sh_hist_opt_norme(char **av, int i, char *opt)
{
	int	j;

	j = 1;
	while (av[i][j])
	{
		if (av[i][j] == 'd')
		{
			if (!av[i + 1])
			{
				return (ft_error(SHELL, av[0],
							"option -d requires an argument") * -1);
			}
			sh_hist_opt_add(opt, av[i][j]);
		}
		else if (av[i][j] == 'c' ||
				av[i][j] == 'r' || av[i][j] == 'w' || av[i][j] == 's')
			sh_hist_opt_add(opt, av[i][j]);
		else
			return (sh_ill_opt(av[0], av[i][j], NULL) * -1);
		j++;
	}
	return (i);
}

int			sh_history_opt(char **av, char *opt)
{
	int	i;

	ft_memset(opt, 0, sizeof(char) * 7);
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "-") || (ft_strequ(av[i], "--") && ++i))
			break ;
		if ((i = sh_hist_opt_norme(av, i, opt)) < 0)
			return (sh_hist_usage());
		i++;
	}
	return (i);
}
