/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:17:22 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/24 16:03:55 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hist_error(char *str)
{
	ft_printf("42sh: history: %s: history out of range\n", str);
	return (0);
}

static void	sh_del_all(t_hist **state)
{
	int		i;

	i = 1;
	while (i - 1 != (*state)->length)
	{
		free((*state)->entry[i].line);
		(*state)->entry[i].line = NULL;
		(*state)->entry[i].timestamp = 0;
	}
	(*state)->offset = 0;
	(*state)->length = 0;
}

static void	sh_del_one(int pos, t_hist **state)
{
	while (pos != (*state)->offset)
	{
		free((*state)->entry[pos].line);
		if (!((*state)->entry[pos].line =
				ft_strdup((*state)->entry[pos + 1].line)))
			return ;
		(*state)->entry[pos].timestamp = (*state)->entry[pos + 1].timestamp;
		pos++;
	}
	free((*state)->entry[pos].line);
	(*state)->length -= 1;
	(*state)->offset = (*state)->length;
}

int			sh_hist_del(char *str)
{
	int		pos;
	t_hist	**state;

	state = global_hist();
	pos = ft_atoi(str);
	if (pos <= 0 || pos > (*state)->length)
	{
		if (!(ft_strcmp(str, "all")))
			sh_del_all(state);
		else
			return (sh_hist_error(str));
	}
	else
		sh_del_one(pos, state);
	return (1);
}
