/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:46:38 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/16 13:34:41 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_init_exit(char **var, size_t size)
{
	while (var[size])
		free(var[size++]);
	free(var);
	return (-1);
}

static int	sh_init_shvar2(void)
{
	struct passwd	*pw;
	char			*home;
	char			*histfile;
	char			*shlvl;
	int				ret;

	histfile = NULL;
	if ((home = sh_getvar("HOME")))
		histfile = ft_strjoin(home, HISTFILE);
	else if ((pw = getpwuid(getuid())))
		hisfile = ft_strjoin(pw->dir, HISTFILE);
	ret += sh_setvar("HISTFILE", histfile ? histfile : HISTFILE);
	if (histfile)
		free(histfile);
	shlvl = ft_itoa(ft_atoi(sh_getvar("SHLVL")) + 1);
	ret += sh_setvar("SHLVL", shlvl);
	if (shlvl)
		free(shlvl);
	return (ret);
}

static int	sh_init_shvar(void)
{
	int				ret;

	ret = 0;
	if (sh_init_shvar2())
		return (1);
	ret += sh_setvar("42SH", 42SH);
	ret += sh_setvar("42SH_COLOR", "false");
	ret += sh_setvar("42SH_VERSION", VERSION);
	ret += sh_setvar("HISTFILESIZE", HISTFILESIZE);
	ret += sh_setvar("HISTSIZE", HISTSIZE);
	ret += sh_setvar("PROMPT_DIRTRIM", PROMPT_DIRTRIM);
	ret += sh_setvar("PS1", PS1);
	ret += sh_setvar("PS2", PS1);
	ret += sh_setvar("PS3", PS1);
	ret += sh_setvar("PS4", PS1);
	return (ret);
}

int			sh_init_var(void)
{
	extern char **environ;
	char		**var;
	size_t		size;

	size = 0;
	while (environ[size])
		size++;
	var = sh_var();
	if (!(var = (char**)memalloc(sizeof(char*) * (size + 1))))
		return (-1);
	while (size--)
	{
		if (!(var[size] = ft_strdup(environ[size])))
			return (ft_init_exit(var, size));
	}
	if (sh_init_shvar())
		return (-1);
	/* ~/.42shrc */
	return (0);
}
