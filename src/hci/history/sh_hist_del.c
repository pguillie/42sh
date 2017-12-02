/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:51:45 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/02 21:47:49 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hist_del(void)
{
	t_line	*tmp;
	t_line	**hist;

	if (!(hist = sh_ghist()) || !*hist)
		return ;
	while ((*hist)->down)
		*hist = (*hist)->down;
	while (*hist)
	{
		tmp = *hist;
		*hist = (*hist)->up;
		free(tmp->str);
		free(tmp);
	}
}
