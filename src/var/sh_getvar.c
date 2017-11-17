/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:47:09 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/17 12:26:29 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_getvar(char *name)
{
	int		i;
	int		j;
	char	***vars;

	if ((vars = sh_var()))
	{
		i = 0;
		j = ft_strlen(name);
		while ((*vars)[i])
		{
			if (ft_strnequ((*vars)[i] + 1, name, j) && (*vars)[i][j + 1] == '=')
				return ((*vars)[i] + j + 2);
			i++;
		}
	}
	return (NULL);
}
