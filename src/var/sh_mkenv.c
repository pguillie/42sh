/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_mkenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:17:15 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/21 15:54:13 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**sh_mkenv(void)
{
	char	***varray;
	char	**env;
	int		i[2];

	if (!(varray = sh_var()))
		return (NULL);
	ft_memset(i, 0, sizeof(int) * 2);
	while ((*varray)[i[0]])
	{
		if ((*varray)[i[0]][0] & V_EXPORT && ft_strchr((*varray)[i[0]], '='))
			i[1]++;
		i[0]++;
	}
	if (!(env = (char**)ft_memalloc(sizeof(char*) * (i[1] + 1))))
		return (NULL);
	ft_memset(i, 0, sizeof(int) * 2);
	while ((*varray)[i[0]])
	{
		if ((*varray)[i[0]][0] & V_EXPORT && ft_strchr((*varray)[i[0]], '='))
			env[i[1]++] = (*varray)[i[0]] + 1;
		i[0]++;
	}
	return (env);
}
