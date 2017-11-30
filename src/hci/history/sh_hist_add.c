/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:01:24 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/30 15:24:49 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hist_error(void)
{
	ft_printf("42sh: history: add fail\n");
	return (1);
}

static void	sh_hist_browse(t_hist **state, int *i)
{
	while (*i < (*state)->size)
	{
		free((*state)->entry[*i].line);
		if (!((*state)->entry[*i].line =
			ft_strdup((*state)->entry[*i + 1].line)))
			return ;
		(*state)->entry[*i].timestamp = (*state)->entry[*i + 1].timestamp;
		*i += 1;
	}
	(*state)->length--;
}

int			sh_hist_add(char *new, int t)
{
	t_hist	**state;
	int		i;

	i = 0;
	if (!(state = global_hist()))
		return (sh_hist_error());
	if (ft_strequ((*state)->entry[(*state)->length - 1].line, new))
		return (0);
	if ((*state)->length == (*state)->size)
		sh_hist_browse(state, &i);
	free((*state)->entry[(*state)->length].line);
	if (!((*state)->entry[(*state)->length].line = ft_strdup(new)))
		return (sh_hist_error());
	if (t == 0 && sh_getvar("HISTTIMEFORMAT"))
		(*state)->entry[(*state)->length].timestamp = time(NULL);
	else
		(*state)->entry[(*state)->length].timestamp = t;
	if (i == 0)
		if (!((*state)->entry[(*state)->length + 1].line = ft_strdup("")))
			return (sh_hist_error());
	(*state)->length += 1;
	(*state)->offset = (*state)->length;
	return (0);
}
