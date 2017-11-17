/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:48:21 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/17 13:59:22 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_setfill(char *new, char *var, char *val)
{
	int		i;
	int		j;
	int		equal;

	equal = 0;
	i = 1;
	j = 0;
	while (var[j])
	{
		if (var[j] == '=')
			equal = 1;
		new[i++] = var[j++];
	}
	if (!equal)
	{
		new[i++] = '=';
		if (val)
		{
			j = 0;
			while (val[j])
				new[i++] = val[j++];
		}
	}
}

static int	sh_setnew(char *var, char *val, int *i, int type)
{
	char	***vars;
	int		l;

	if (!(vars = sh_var()))
		return (-1);
	if (i[1] < 0)
	{
		if (!(*vars = (char**)ft_realloc(*vars, i[0] + 1, i[0] + 2, sizeof(char*))))
			return (-1);
		i[1] = i[0];
	}
	if (ft_strchr(var, '='))
		l = ft_strlen(var) + 1;
	else
		l = ft_strlen(var) + ft_strlen(val) + 2;
	if (!((*vars)[i[1]] = ft_strnew(l)))
		return (-1);
	(*vars)[i[1]][0] = type;
	sh_setfill((*vars)[i[1]], var, val);
	return (0);
}

int			sh_setvar(char *var, char *val)
{
	int		i[2];
	int		l;
	int		type;
	char	***vars;

	if (!var || !(vars = sh_var()))
		return (-1);
	l = 0;
	while (var[l] && var[l] != '=')
		l++;
	i[0] = 0;
	i[1] = -1;
	type = 0;
	while ((*vars)[i[0]])
	{
		if (ft_strnequ((*vars)[i[0]] + 1, var, l) && (*vars)[i[0]][l] == '=')
		{
			if ((type = (*vars)[i[0]][0]) & V_READONLY)
				return (1);
			free((*vars)[i[0]]);
			i[1] = i[0];
		}
		i[0]++;
	}
	return (sh_setnew(var, val, i, type));
}
