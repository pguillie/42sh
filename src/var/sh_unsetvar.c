/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:22:43 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/03 13:36:03 by ysan-seb         ###   ########.fr       */
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

static int	sh_unsetvar_mod(int line, char type)
{
	char vtype;
	char ***vray;

	if (!(vray = sh_var()))
		return (-1);
	vtype = (*vray)[line][0];
	if (type & V_RDONLY)
		return (V_RDONLY);
	else
		(*vray)[line][0] = ~(~(vtype) | type);
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
				&& (*vray)[i][len + 1] == '=')
			line = i;
		i++;
	}
	if (line < 0)
		return (0);
	if (!type)
		return (sh_unsetvar_del(line, i));
	else
		return (sh_unsetvar_mod(line, type));
}
