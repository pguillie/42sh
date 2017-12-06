/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:04 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/06 16:52:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_disp_nl(t_line *line, t_coord *coord, t_tc tc, size_t i)
{
	if (i && line->str[i - 1] != '\n'
			&& line->cur != i
			&& coord[i - 1].x == coord[line->used + 1].x - 1)
	{
		ft_putchar_fd(' ', 0);
		tputs(tc.le, 0, termput);
	}
}

int			sh_display(t_line *l, t_coord **coord, t_tc tc, char *save)
{
	char	*color;
	size_t	i;

	i = l->cur;
	color = sh_getvar("42SH_COLOR");
	if (!color || (ft_strcmp(color, "true") && ft_strcmp(color, "on")) || save)
	{
		if (sh_clear(l, coord, tc) < 0)
			return (-1);
		while (l->str[i])
		{
			ft_putchar_fd(l->str[i++], 0);
			sh_disp_nl(l, *coord, tc, i);
		}
	}
	else
	{
		l->cur = sh_move_cur(l->cur, 0, *coord, tc);
		if (sh_clear(l, coord, tc) < 0)
			return (-1);
		sh_display_syntax(l->str);
		sh_disp_nl(l, *coord, tc, l->used);
	}
	l->cur = sh_move_cur(l->used, l->pos, *coord, tc);
	return (0);
}
