/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:22:43 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/06 13:54:24 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_unsetvar_del(int line, int size)
{
	int		i;
	int		j;
	char	**new;
	char	***vray;

	if (!(vray = sh_var()))
		return (-1);
	if (!(new = (char **)ft_memalloc(sizeof(char *) * size)))
		return (-1);
	i = 0;
	j = 0;
	while ((*vray)[i])
	{
		if (i != line)
			new[j++] = (*vray)[i];
		i++;
	}
	free((*vray)[line]);
	free((*vray));
	(*vray) = new;
	return (0);
}

int			sh_unsetvar(char *name, char type, char search)
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
		if ((!search || (*vray)[i][0] & search)
				&& ft_strnequ((*vray)[i] + 1, name, len)
				&& ((*vray)[i][len + 1] == '=' || !(*vray)[i][len + 1]))
			line = i;
		i++;
	}
	if (line < 0)
		return (0);
	if (((*vray)[line][0] & V_RDONLY) && (!type || type & V_RDONLY))
		return (V_RDONLY);
	if (type)
		(*vray)[line][0] = ~(~(*vray)[line][0] | type);
	return (type ? 0 : sh_unsetvar_del(line, i));
}
