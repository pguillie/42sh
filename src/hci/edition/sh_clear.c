/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:10 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/06 16:51:38 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_clear(t_line *line, t_coord **coord, t_tc tc)
{
	int		i;
	int		j;
	t_coord	*new_coord;

	tputs(tc.ce, 0, termput);
	if (!(new_coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	j = 0;
	while ((*coord)[j].y >= 0)
		j++;
	if (j && (*coord)[j - 1].y)
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
