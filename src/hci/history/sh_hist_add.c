/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:01:24 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/27 09:49:32 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hist_error(void)
{
	ft_printf("42sh: history: add fail\n");
	return (1);
}

static void	sh_hist_browse(t_hist **state)
{
	int		i;

	i = 1;
	while (i < (*state)->size)
	{
		free((*state)->entry[i].line);
		if (!((*state)->entry[i].line = ft_strdup((*state)->entry[i + 1].line)))
			return ;
		(*state)->entry[i].timestamp = (*state)->entry[i + 1].timestamp;
		i++;
	}
	free((*state)->entry[i].line);
}

int			sh_hist_add(char *new)
{
	t_hist	**state;

	if (!(state = global_hist()))
		return (sh_hist_error());
	if ((*state)->length >= (*state)->size)
		sh_hist_browse(state);
	else
	{
		(*state)->length += 1;
		(*state)->offset = (*state)->length;
	}
	if (!((*state)->entry[(*state)->length].line = ft_strdup(new)))
		return (sh_hist_error());
	// if (sh_getvar("HISTTIMEFORMAT"))
	// 	(*state)->entry[(*state)->length].timestamp = time(NULL);
	return (0);
}
