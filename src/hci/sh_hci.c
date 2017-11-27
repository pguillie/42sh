/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hci.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:03:44 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/22 11:03:45 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_line	*sh_hline_new(char *str)
{
	t_line	*new;

	if (!(new = (t_line*)ft_memalloc(sizeof(t_line))))
		return (NULL);
	new->capacity = ((ft_strlen(str) + 1) / BUFF_SIZE + 1) * BUFF_SIZE;
	if (!(new->str = ft_strnew(new->capacity)))
	{
		ft_memdel((void**)new);
		return (NULL);
	}
	ft_strcat(new->str, str);
	new->used = ft_strlen(str);
	new->cur = 0;
	return (new);
}

int		sh_hci(t_tc *tc, t_token **lexer, int mret)
{
	t_hist	**hist;
	t_line	*line;
	char	*last;
	int		ret;

	if (!(hist = global_hist()))
	 	return (ft_error(E_SEVER, NULL, NULL));
	if (!(line = sh_hline_new("")))
		return (-1);
	ret = 0;
	last = NULL;
	if (g_signal != SIGINT)
	{
		//last = hist->up ? ft_strjoin(hist->up->str, "\n") : NULL;.

		ret = sh_edit(line, last, lexer, tc);
		last ? ft_strdel(&last) : 0;
	}
	// sh_hist_del(&hist);
	if (g_signal == SIGINT)
		write(1, "\n", 1);
	if (ret >= 0 && ret & EOT)
		sh_exit(NULL, mret);
	if (ret < 0)
		return (ft_error(E_SEVER, NULL, NULL));
	return (0);
}
