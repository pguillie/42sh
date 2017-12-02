/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:50:23 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:50:38 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hash_indapp(int new)
{
	int	*hindex;
	int	i;

	hindex = sh_hindex();
	i = 0;
	while (i < HASH_SIZE - 1 && hindex[i] >= 0)
		i++;
	hindex[i] = new;
}

int		sh_hash_set(char *cmd, char *path)
{
	t_htable	**htable;
	t_htable	*ctable;
	t_htable	*ntable;
	int			index;

	htable = sh_htable();
	index = sh_hash_fct(cmd);
	if (!(ntable = sh_hash_new(cmd, path)))
		return (-1);
	if (!(ctable = htable[index]))
	{
		htable[index] = ntable;
		sh_hash_indapp(index);
	}
	else
	{
		while (ctable->next)
			ctable = ctable->next;
		ctable->next = ntable;
	}
	return (0);
}
