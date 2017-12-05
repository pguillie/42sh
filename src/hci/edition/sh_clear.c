/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:10 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/05 02:06:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_clear(t_line *line, t_coord **coord, t_tc tc)
{
	int		i;
	size_t	l;
	t_coord	*new_coord;

	tputs(tc.ce, 0, termput);
	if (!(new_coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	l = 0;
	while (l <= line->used && (*coord)[l].y != new_coord[line->used + 1].y
			&& (*coord)[l].x != new_coord[line->used + 1].x)
		l++;
	if ((*coord)[l - 1].y > new_coord[line->cur].y)
	{
		ft_putstr("\n\r");
		tputs(tc.cd, 0, termput);
		tputs(tc.up, 0, termput);
		i = 0;
		while (i++ < new_coord[line->cur].x)
			tputs(tc.nd, 0, termput);
	}
	free(*coord);
	*coord = new_coord;
	return (0);
}
