/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_disp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:24:07 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/24 16:27:47 by mdescamp         ###   ########.fr       */
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

	i = 1;
	if (!(state = global_hist()))
	return ;
	while (i - 1 != (*state)->length)
	{
		// if (sh_getvar("HISTTIMEFORMAT"))
		// {
			test = ((*state)->entry[i].timestamp) == 0 ?
					(time(NULL)) : ((*state)->entry[i].timestamp);
			if (!(tm = localtime(&test)))
				return ;
			if (strftime(tmp, 128, "%a %b %d %T ", tm) == 0)//sh_getvar("HISTTIMEFORMAT")
				return ;
			ft_printf("%5d  %s%s\n", i, tmp, (*state)->entry[i].line);
		// }
		// else
			// ft_printf("%5d  %s", i, (*state)->entry[i].line);
		i++;
	}
}
