/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:00:42 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 14:44:25 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hist_w(t_line *h)
{
	int		fd;

	if ((fd = open(sh_getvar("HISTFILE"), O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR)) < 0)
		return (-1);
	while (h->up)
		h = h->up;
	while (h)
	{
		sh_hwrite(h->str, fd, h->down ? 1 : 0);
		h = h->down;
	}
	return (0);
}

int			sh_hist_add(void)
{
	t_line	*h;

	h = sh_hist_read();
	while (h->down)
		h = h->down;
	if (h->up)
		h = h->up;
	else
		return (-1);
	ft_memmove(h->str, h->str + 11, ft_strlen(h->str + 11) + 1);
	sh_hist_w(h);
	return (0);
}
