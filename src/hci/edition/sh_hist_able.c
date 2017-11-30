/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_able.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:53:55 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/30 15:25:28 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_convert_hist(char *esc)
{
	if (esc[1] == '[' && (esc[2] == 'A' || esc[2] == 'B'))
		return ((esc[2] ^ 64) | 4);
	else if (esc[1] == '[' && (esc[2] == '5' || esc[2] == '6') && esc[3] == '~')
		return (esc[2] ^ 52);
	return (0);
}

static int	sh_hist_search(t_line *line, int id)
{
	if (id & HIST_SEARCH)
	{
		if (!line->h_smd)
		{
			line->h_smd = 1;
			line->h_pos = line->cur;
		}
		return (1);
	}
	else
		return (0);
}

static int	sh_hist_comp(t_line *line, char c)
{
	t_hist	**hist;
	int		i;

	if (!(hist = global_hist()))
		return (0);
	i = (*hist)->offset;
	if (c == '-' && (*hist)->offset > 1 && (*hist)->entry[i].line &&
			(!ft_strnequ(line->str, (*hist)->entry[i].line, line->h_pos)
				|| !ft_strcmp(line->str, (*hist)->entry[i].line)))
		return (1);
	else if (c == '+' && i < (*hist)->length && (*hist)->entry[i].line &&
			(!ft_strnequ(line->str, (*hist)->entry[i].line, line->h_pos)
			|| !ft_strcmp(line->str, (*hist)->entry[i].line)))
		return (1);
	return (0);
}

static char	*sh_get_target(t_line *line, char *target, int id)
{
	if (id & UP)
	{
		if (line->h_smd)
			while (sh_hist_comp(line, '-'))
				target = sh_hist_move('-');
	}
	else if (id & DOWN)
	{
		if (line->h_smd)
			while (sh_hist_comp(line, '+'))
				target = sh_hist_move('+');
	}
	if (id & DOWN && (!target || !ft_strnequ(target, line->str, line->h_pos)))
		return (line->tmp);
	if (!target || !ft_strnequ(target, line->str, line->h_pos))
		return (line->str);
	return (target);
}

char		*sh_hist_able(char *esc, t_line *line, int *hist_search)
{
	char	*target;
	int		id;

	target = NULL;
	id = sh_convert_hist(esc);
	if (!line->h_smd)
	{
		free(line->tmp);
		line->tmp = ft_strdup(line->str);
	}
	*hist_search = sh_hist_search(line, id);
	target = sh_get_target(line, target, id);
	return (target);
}
