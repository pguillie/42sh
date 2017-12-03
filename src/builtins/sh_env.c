/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:12:47 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/03 12:38:34 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_env_opt(char **av)
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
			if (av[i][j] != 'i')
				return (-av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

static int	sh_env_append(char ***e, char *var)
{
	int		i[3];

	ft_memset(i + 1, 0, sizeof(int) * 2);
	while (var[i[1]] && var[i[1]] != '=')
		i[1]++;
	if ((i[0] = -1) && i[1] == 0)
		return (1);
	if (*e)
	{
		while ((*e)[i[2]])
		{
			if (ft_strnequ((*e)[i[2]], var, i[1]) && (*e)[i[2]][i[1]] == '=')
				i[0] = i[2];
			i[2]++;
		}
	}
	if (i[0] >= 0)
		(*e)[i[0]] = var;
	else
	{
		if (!(*e = (char**)ft_realloc(*e, i[2] + 1, i[2] + 2, sizeof(char*))))
			return (-1);
		(*e)[i[2]] = var;
	}
	return (0);
}

static void	sh_env_print(char **env)
{
	int		i;

	if (env)
	{
		i = 0;
		while (env[i])
			ft_putendl(env[i++]);
	}
}

static int	sh_env_exec(char **av)
{
	pid_t	child;
	int		ret;

	ret = 0;
	if ((child = fork()) < 0)
		return (-1);
	else if (child == 0)
		exit(sh_execution(av, 0, 1, 0));
	return (sh_wait(child, ret));
}

int			sh_env(char **av)
{
	extern char	**environ;
	int			ret;
	int			i;

	if ((i = sh_env_opt(av)) < 0)
		return (sh_ill_opt(av[0], -i, SH_ENV));
	if (i > 1)
	{
		free(environ);
		environ = NULL;
	}
	while (ft_strchr(av[i], '='))
		sh_env_append(&environ, av[i++]);
	ret = 0;
	if (av[i])
		ret = sh_env_exec(av + i);
	else
		sh_env_print(environ);
	return (ret);
}
