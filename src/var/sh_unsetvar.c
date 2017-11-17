/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:22:43 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/17 13:59:10 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		sh_unsetvar_del(int line, int size)
{
	int		i;
	int		j;
	char	**new;
	char	***vray;

	if (!(vray = sh_var()))
		return (-1);
	if (!(new = (char **)ft_memalloc(char *) * size))
		return (-1);
	i = 0;
	j = 0;
	while ((*vray)[i])
	{
		if (i != line)
			new[j++] = (*vray)[i];
		i++;
	}
	free((*vray));
	free((*vray)[line]);
	(*vray) = new;
	return (0);
}

static int		sh_unsetvar_mod(int line, char type)
{
	char vtype;
	char ***vray;

	if (!(vray = sh_var()))
		return (-1);
	vtype = (*vray)[line][0];
	if (type & V_RDONLY)
		return (V_RDONLY);
	else
		(*vray)[line][0] = ~((vtype) | type);
	return (0);
}

int				sh_unsetvar(char *name, char type)
{
	int		i;
	int		len;
	int		line;
	char	***vray;

	if (!(vray = sh_var()) || !name)
		return (-1);
	i = 0;
	line = -1;
	len = ft_strlen(name);
	while ((*vray)[i])
	{
		if (strnequ((*vray)[i] + 1, name, len) && (*vray)[i][j + 1] == '=')
			line = i;
		i++;
	}
	if (!line)
		return (0);
	if (!type)
		return (sh_unsetvar_del(line, i));
	else
		return (sh_unsetvar_mod(line, type));
}
