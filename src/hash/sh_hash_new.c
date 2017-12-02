/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:50:26 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:50:38 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_htable	*sh_hash_new(char *cmd, char *path)
{
	t_htable	*new;

	if (!(new = (t_htable*)ft_memalloc(sizeof(t_htable))))
		return (NULL);
	new->cmd = ft_strdup(cmd);
	new->path = ft_strdup(path);
	if (!new->cmd || !new->path)
	{
		new->cmd ? free(new->cmd) : 0;
		new->path ? free(new->path) : 0;
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
