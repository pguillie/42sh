/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:46:38 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/16 17:20:46 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_init_exit(char ***vars, size_t size)
{
	while ((*vars)[size])
		free((*vars)[size++]);
	free(*vars);
	*vars = NULL;
	return (-1);
}

static int	sh_init_shvar2(void)
{
	struct passwd	*pw;
	char			*home;
	char			*histfile;
	char			*shlvl;
	int				ret;

	ret = 0;
	histfile = NULL;
	if ((home = sh_getvar("HOME")))
		histfile = ft_strjoin(home, HISTFILE);
	else if ((pw = getpwuid(getuid())))
		histfile = ft_strjoin(pw->pw_dir, HISTFILE);
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
	ret += sh_setvar("42SH", SHELL);
	ret += sh_setvar("42SH_COLOR", "false");
	ret += sh_setvar("42SH_VERSION", VERSION);
	ret += sh_setvar("HISTFILESIZE", HISTFILESIZE);
	ret += sh_setvar("HISTSIZE", HISTSIZE);
	ret += sh_setvar("PS1", PS1);
	ret += sh_setvar("PS2", PS2);
	ret += sh_setvar("PS3", PS3);
	ret += sh_setvar("PS4", PS4);
	return (ret);
}

int			sh_init_var(void)
{
	extern char **environ;
	char		***vars;
	size_t		size;

	size = 0;
	while (environ[size])
		size++;
	vars = sh_var();
	if (!((*vars) = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		return (-1);
	while (size--)
	{
		if (!((*vars)[size] = ft_strnew(ft_strlen(environ[size]) + 1)))
			return (sh_init_exit(vars, size + 1));
		(*vars)[size][0] = V_EXPORT;
		ft_strcat((*vars)[size], environ[size]);
	}
	if (sh_init_shvar())
		return (-1);
	/* ~/.42shrc */
	return (0);
}
