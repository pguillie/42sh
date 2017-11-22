/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:46:57 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/22 17:18:10 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* 1: contenu
 * 2: X
 * 3: /
 * 4: . ..
 * 5: cdpath
 * => 6: valid
 * 7-9: travailler la chaine si -L
 * 10: chdir
 */

static int	sh_cd_opt(char **av, char *opt)
{
	int		i;
	int		j;

	*opt = 'L';
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--") && ++i)
			break ;
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'L' || av[i][j] == 'P')
				*opt = av[i][j];
			else
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return  (i);
}

int			sh_cd(char **av)
{
	char	*dir;
	char	opt;
	int		i;

	if ((i = sh_cd_opt(av, &opt)) < 0)
		return (sh_ill_opt(av[0], -i, SH_CD));
	if (!(dir = (av[i] ? av[i] : sh_getvar("HOME"))))
		return (ft_error(SHELL, av[0], "HOME not set"));
	if (!(dir = sh_cd_path(dir)))
		return (-1);
	if (opt == 'L' && sh_cd_cn(&dir))
		return (ft_error(SHELL, av[0], E_NOENT));
	
}
