/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 10:00:04 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/30 18:26:45 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_insert(t_line *line, char *exp, int i)
{
	char	*res;
	int		len;

	line->cur = i;
	len = ft_strlen(exp);
	res = NULL;
	if (line->used + ft_strlen(exp) >= line->capacity)
	{
		line->capacity += BUFF_SIZE * ((len / BUFF_SIZE) + 1);
		if (!(line->str = ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + len, line->str + line->cur,
			ft_strlen(line->str + line->cur) + 1);
	ft_strncpy(line->str + line->cur, exp, len);
	line->used += len;
	line->pos = line->cur + ft_strlen(exp);
	return (0);
}

int			sh_hist_exp(t_line *line, int ret)
{
	t_hist	**hist;
	char	*exp;
	int		i;
	int		b;

	i = 0;
	b = 0;
	if (!(hist = global_hist()))
		return (-1);
	while ((i = sh_histexp_id(line->str, i)) >= 0)
	{
		b = 1;
		exp = NULL;
		if (sh_histexp_event(line->str, i, &exp, *hist))
			return (-1);
		if (sh_histexp_word(line->str, i, &exp))
			return (-1);
//		if (sh_histexp_modif(str, i, &exp))
//			return (-1);
		if (exp)
			sh_insert(line, exp, i);
		exp ? free(exp) : 0;
	}
	b ? ft_putstr(line->str) : 0;
	return (ret);
}
