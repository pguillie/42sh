/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:56:15 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/17 17:00:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_setvar_fil(char *var, char *name, char *value, char type)
{
	var[0] = type;
	ft_strcat(var, name);
	if (value)
	{
		ft_strcat(var, "=");
		ft_strcat(var, value);
	}
}

static int	sh_setvar_new(char *name, char *value, char type, int size)
{
	char	***varray;
	char	**new;
	char	*var;
	int		i;

	varray = sh_var();
	if (!varray || !(var = ft_strnew(ft_strlen(name) + 1
					+ (value ? ft_strlen(value) + 1 : 0))))
		return (-1);
	if (!(new = (char**)ft_memalloc(sizeof(char*) * size + 2)))
	{
		free(var);
		return (-1);
	}
	sh_setvar_fil(var, name, value, type);
	i = 0;
	while ((*varray)[i])
	{
		new[i] = (*varray)[i];
		i += 1;
	}
	new[i] = var;
	free(*varray);
	*varray = new;
	return (0);
}

static int	sh_setvar_mod(char *name, char *value, char type, int i)
{
	char	***varray;
	char	*var;

	if (!(varray = sh_var()))
		return (-1);
	if (value)
	{
		if (!(var = ft_strnew(ft_strlen(name) + ft_strlen(value) + 2)))
			return (-1);
		sh_setvar_fil(var, name, value, (*varray)[i][0] | type);
		(*varray)[i] = var;
	}
	else
		(*varray)[i][0] |= type;
	return (0);
}

int			sh_setvar(char *name, char *value, char type)
{
	char	***varray;
	int		size;
	int		i;
	int		len;

	if (!name || !(varray = sh_var()))
		return (-1);
	i = -1;
	len = ft_strlen(name);
	size = 0;
	while ((*varray)[size])
	{
		if (ft_strncmp((*varray)[size] + 1, name, len)
			&& (*varray)[size] + len == '=')
			i = size;
		size += 1;
	}
	if (i < 0)
		return (sh_setvar_new(name, value, type, size));
	else
		return (sh_setvar_mod(name, value, type, i));
}
