/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:06 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:53:12 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_del_l(t_line *line, t_coord **coord, t_tc tc)
{
	if (!line->cur)
		return (0);
	line->cur = sh_move_cur(line->cur, line->cur - 1, *coord, tc);
	return (sh_del_r(line));
}

int		sh_del_r(t_line *line)
{
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
		ft_strlen(line->str + line->cur + 1) + 1);
	line->used -= 1;
	line->pos = line->cur;
	return (LEXER | DISP);
}
