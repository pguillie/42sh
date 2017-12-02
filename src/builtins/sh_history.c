/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 10:50:13 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 11:14:38 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_history(char **av)
{
	char	opt[7];
	int		i;
	int		j;

	if ((i = sh_history_opt(av, opt)) < 0)
		return (1);
	j = 0;
/*	while (opt[j])
	{
		if (opt[j] == 's')
			sh_hist_add(av[i], 0);
		else if (opt[j] == 'r')
			sh_hist_read();
		else if (opt[j] == 'w')
			sh_hist_write();
		else if (opt[j] == 'c')
			sh_hist_del("all");
		else if (opt[j] == 'd')
			sh_hist_del(av[i]);
		j++;
	}
	if (j == 0)
		sh_hist_disp();
*/	return (0);
}
