/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_disp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:24:07 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/30 16:42:39 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hist_disp(void)
{
	t_hist		**state;
	int			i;
	long		test;
	char		tmp[128];
	struct tm	*tm;

	i = 0;
	if (!(state = global_hist()))
		return ;
	while (i != (*state)->length)
	{
		if (sh_getvar("HISTTIMEFORMAT"))
		{
			test = ((*state)->entry[i].timestamp) == 0 ?
					(time(NULL)) : ((*state)->entry[i].timestamp);
			if (!(tm = localtime(&test)))
				return ;
			if (strftime(tmp, 128, sh_getvar("HISTTIMEFORMAT"), tm) == 0)
				return ;
			ft_printf("%5d  %s%s\n", i + 1, tmp, (*state)->entry[i].line);
		}
		else
			ft_printf("%5d  %s\n", i + 1, (*state)->entry[i].line);
		i++;
	}
}
