/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:50:28 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:50:38 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_hash_get(char *cmd)
{
	t_htable	**htable;
	t_htable	*ctable;

	htable = sh_htable();
	ctable = htable[sh_hash_fct(cmd)];
	while (ctable && !ft_strequ(ctable->cmd, cmd))
		ctable = ctable->next;
	if (ctable)
		return (ctable->path);
	return (NULL);
}
