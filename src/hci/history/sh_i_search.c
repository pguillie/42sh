/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_i_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:20:00 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/01 17:24:04 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_i_print(t_hist *hist, char *str, t_tc *tc, int *goffset)
{
	int		y;
	t_line	*line;

	tputs(tc->cd, 0, termput);
	if (!(line = ft_memalloc(sizeof(t_line))))
		return ;
	if (!hist)
		line->str = ft_strdup("");
	else if (sh_cpy_hist(hist, goffset, &line) < 0)
	{
		free(line);
		return ;
	}
	sh_i_prompt(str, tc, goffset[0]);
	ft_putstr(line->str);
	free(tc->coord);
	tc->coord = sh_create_coord(line, 21 + ft_strlen(str));
	y = tc->coord[line->used].y;
	while (y--)
		tputs(tc->up, 0, termput);
	ft_putstr("\r");
	line->str ? free(line->str) : 0;
	line ? free(line) : 0;
}

static void	sh_i_find(t_hist *hist, int *goffset, t_tc *tc, char *tmp)
{
	int ret;

	while (goffset[1] >= 0 && goffset[1] < hist->length)
	{
		ret = 0;
		if ((ret = sh_i_strstr(hist->entry[goffset[1]].line, tmp, goffset[0])))
		{
			goffset[3] = 1;
			goffset[2] = goffset[1];
			sh_i_print(hist, tmp, tc, goffset);
			break ;
		}
		goffset[1] += goffset[0] * 2 - 1;
	}
	if (!ret && goffset[3] &&
			sh_i_strstr(hist->entry[goffset[2]].line, tmp, goffset[0]))
		sh_i_print(hist, tmp, tc, goffset);
}

static int	sh_i_read(t_hist *hist, int *goffset, t_tc *tc)
{
	char	*tmp;
	char	byte[8];

	tmp = NULL;
	ft_bzero(byte, 8);
	if (!hist->entry[goffset[1]].line[0])
		goffset[1] += goffset[1] * 2 - 1;
	while (read(0, &byte, 8) >= 0 && byte[0] != '\n' && g_signal != SIGINT)
	{
		if (byte[0] == 27 || g_signal == SIGWINCH)
		{
			free(tmp);
			return (1);
		}
		else if (byte[0] == 127)
			tmp = sh_del_char(tmp);
		else
			tmp = sh_ins_char(tmp, byte[0]);
		sh_i_find(hist, goffset, tc, tmp);
	}
	free(tmp);
	return (goffset[2] == goffset[1] ? 0 : 1);
}

static int	sh_end(t_line **line, t_tc *tc, int ret)
{
	tputs(tc->cd, 0, termput);
	free(tc->coord);
	tc->coord = sh_create_coord(*line, sh_prompt(1));
	g_signal = 0;
	*line ? tc->coord[(*line)->used].y = 0 : 1;
	if (ret == 0)
	{
		*line ? ft_putstr((*line)->str) : 1;
		(*line)->cur = (*line)->used;
		return (sh_nl(*line, &tc->coord, *tc));
	}
	return (DISP);
}

int			sh_i_search(t_line **line, t_tc *tc, int mode)
{
	int		goffset[4];
	t_hist	**hist;
	int		ret;

	if (!(hist = global_hist()))
		return (1);
	(*line)->pos = sh_move_cur((*line)->pos, 0, tc->coord, *tc);
	(*line)->cur = 0;
	goffset[0] = mode;
	goffset[1] = mode ? 0 : (*hist)->length - 1;
	goffset[2] = goffset[1];
	goffset[3] = 0;
	free((*line)->str);
	(*line)->str = NULL;
	sh_i_print(NULL, NULL, tc, goffset);
	ret = sh_i_read(*hist, goffset, tc);
	if (sh_cpy_hist(*hist, goffset, line) < 0)
		return (1);
	return (sh_end(line, tc, ret));
}
