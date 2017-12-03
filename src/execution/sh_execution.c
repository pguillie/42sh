/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 11:06:15 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/03 12:01:23 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_exec_hash(char **av, int pipe)
{
	extern char	**environ;
	char		*path;
	int			ret;

	path = sh_hash_get(av[0]);
	if (path)
	{
		free(av[0]);
		if (!(av[0] = ft_strdup(path)))
			return (-1);
	}
	ret = sh_cmd_exec(av, environ, &path, pipe);
	if (!ft_strchr(av[0], '/'))
		sh_hash_set(av[0], path);
	path ? free(path) : 0;
	return (ret);
}

static int	sh_builtin2(char **av, int *ret)
{
	if (ft_strequ(av[0], "readonly"))
		*ret = sh_readonly(av);
	else if (ft_strequ(av[0], "setenv"))
		*ret = sh_setenv(av);
	else if (ft_strequ(av[0], "unset"))
		*ret = sh_unset(av);
	else if (ft_strequ(av[0], "unsetenv"))
		*ret = sh_unsetenv(av);
	else
		return (0);
	return (1);
}

static int	sh_builtin(char **av, int *ret)
{
	if (ft_strequ(av[0], "cd"))
		*ret = sh_cd(av);
	else if (ft_strequ(av[0], "declare"))
		*ret = sh_declare(av);
	else if (ft_strequ(av[0], "echo"))
		*ret = sh_echo(av);
	else if (ft_strequ(av[0], "env"))
		*ret = sh_env(av);
	else if (ft_strequ(av[0], "exit"))
		*ret = sh_exit(av, *ret);
	else if (ft_strequ(av[0], "export"))
		*ret = sh_export(av);
	else if (ft_strequ(av[0], "hash"))
		*ret = sh_hash(av);
	else if (ft_strequ(av[0], "history"))
		*ret = sh_history(av);
	else if (ft_strequ(av[0], "printenv"))
		*ret = sh_printenv(av[1]);
	else if (!sh_builtin2(av, ret))
		return (0);
	return (1);
}

int			sh_execution(char **av, int ret, int pipe, int sub)
{
	if (sh_builtin(av, &ret))
		return (ret);
	else if (sub)
		return (sh_sub_shell(av[0]));
	else
		return (sh_exec_hash(av, pipe));
}
