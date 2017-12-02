/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:54:26 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:54:26 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hist_del(void)
{
	t_line	*tmp;
	t_line	**hist;

	if (!(hist = sh_ghist()))
		return ;
	while (*hist)
	{
		tmp = *hist;
		*hist = (*hist)->up;
		ft_strdel(&tmp->str);
		ft_memdel((void**)&tmp);
	}
}
