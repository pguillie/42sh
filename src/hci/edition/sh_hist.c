/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:52:55 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:53:12 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_hist(t_line **line, t_coord **coord, t_tc tc, t_line *target)
{
	(*line)->cur = sh_move_cur((*line)->cur, 0, *coord, tc);
	target->h_smd = (*line)->h_smd;
	target->h_pos = (*line)->h_pos;
	*line = target;
	(*line)->pos = (*line)->used;
	return (LEXER | DISP);
}
