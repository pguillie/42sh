/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:34:53 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/23 16:51:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_cd_access2(char *path, char *dir)
{
	struct stat	s;

	if (access(path, F_OK) < 0)
		return (ft_error("cd", dir, E_NOENT));
	if (stat(path, &s) < 0)
		return (-1);
	if (!S_ISDIR(s.st_mode))
		return (ft_error("cd", dir, E_NODIR));
	if (access(path, X_OK) < 0)
		return (ft_error("cd", dir, E_NORGHT));
	return (0);
}

int			sh_cd_access(char *path, char *dir)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (i && path[i] == '/')
		{
			path[i] = 0;
			if (sh_cd_access2(path, dir))
				return (1);
			path[i] = '/';
		}
		i++;
	}
	return (sh_cd_access2(path, dir));
}
