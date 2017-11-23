/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:10:29 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/23 16:51:23 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_cd2(char *dir, char *path, char opt)
{
	char	*cwd;

	cwd = NULL;
	if (chdir(path) < 0)
	{
		return (ft_error("cd", dir,
					(access(path, F_OK) ? E_NOENT : E_NORGHT)));
	}
	if (ft_strequ(dir, "-"))
		ft_putendl(path);
	if ((sh_setvar("OLDPWD", sh_getvar("PWD"), 0) < 0) ||
			(sh_setvar("PWD", (opt == 'P' ?
					(cwd = getcwd(NULL, 0)) : path), 0) < 0))
		return (-1);
	if (cwd)
		free(cwd);
	return (0);
}
