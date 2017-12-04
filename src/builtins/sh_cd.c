/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:02:24 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/04 12:13:51 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_cd_opt(char **av, char *opt)
{
	int		i;
	int		j;

	*opt = 'L';
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "-") || (ft_strequ(av[i], "--") && ++i))
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
	return (i);
}

static char	*sh_cdpath(char *dir)
{
	char	**cdpath;
	char	*path;
	size_t	i;

	if (!(cdpath = sh_varsplit(sh_getvar("CDPATH"))))
		return (NULL);
	path = NULL;
	i = 0;
	while (cdpath[i])
	{
		path = ft_strcjoin(cdpath[i] ? cdpath[i] : ".", dir, '/');
		if (path)
		{
			if (access(path, F_OK) == 0 || !cdpath[i + 1])
				break ;
			free(path);
			path = NULL;
		}
		i++;
	}
	ft_strtabdel(cdpath);
	return (path);
}

static int	sh_cd_absolute(char *dir, char **path)
{
	char	*pwd;

	if (ft_strequ(dir, "-"))
	{
		return ((*path = ft_strdup(sh_getvar("OLDPWD"))) ? 0
				: ft_error("cd", E_NOVAR("OLDPWD"), NULL));
	}
	if (dir[0] == '/')
		return ((*path = ft_strdup(dir)) ? 0 : 1);
	if (ft_strnequ(dir, "./", 2) || ft_strnequ(dir, "../", 3)
			|| ft_strequ(dir, ".") || ft_strequ(dir, ".."))
		*path = ft_strdup(dir);
	else
		*path = sh_cdpath(dir);
	if (!*path || *path[0] == '/')
		return (*path ? 0 : 1);
	if (!(pwd = sh_getvar("PWD")) || pwd[0] != '/')
	{
		free(*path);
		return (ft_error(SHELL, "cd", (pwd ? "invalid PWD" : E_NOVAR("PWD"))));
	}
	dir = *path;
	*path = ft_strcjoin(pwd, dir, '/');
	free(dir);
	return (*path ? 0 : -1);
}

static char	*sh_cd_l(char *path)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (path[i])
	{
		if (ft_strnequ(path + i, "/./", 3) || ft_strequ(path + i, "/."))
			ft_memmove(path + i + 1, path + i + 2, ft_strlen(path + i + 1));
		else if (ft_strnequ(path + i, "//", 2))
			ft_memmove(path + i, path + i + 1, ft_strlen(path + i));
		else if (ft_strnequ(path + i, "/../", 4) || ft_strequ(path + i, "/.."))
		{
			j = i > 0 ? i - 1 : 0;
			while (j && path[j] != '/')
				j--;
			ft_memmove(path + j + 1, path + i + 2, ft_strlen(path + i + 1));
			i = j;
		}
		else if (ft_strequ(path + i, "/") && i)
			path[i] = '\0';
		else
			i++;
	}
	return (path);
}

int			sh_cd(char **av)
{
	char	*dir;
	char	*save;
	char	opt;
	int		ret;
	int		i;

	dir = NULL;
	if ((i = sh_cd_opt(av, &opt)) < 0)
		return (sh_ill_opt(av[0], -i, SH_CD));
	save = av[i];
	if (!av[i] && !(av[i] = sh_getvar("HOME")))
		return (ft_error(SHELL, av[0], "HOME not set"));
	if ((ret = sh_cd_absolute(av[i], &dir)))
	{
		av[i] = save;
		return (ret < 0 ? -ft_error(SHELL, E_SEVER, NULL) : 1);
	}
	if (!(ret = sh_cd_access(dir, ft_strcmp(av[i], "-") ? av[i] : dir)))
	{
		dir = (opt == 'L' ? sh_cd_l(dir) : dir);
		ret = sh_cd2(av[i], dir, opt) < 0;
	}
	free(dir);
	av[i] = save;
	return (ret);
}
