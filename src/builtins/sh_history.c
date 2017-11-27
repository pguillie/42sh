/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:23:00 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/27 16:12:24 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_history(char **av)
{
	char	opt[7];
	int		i;
	int		j;

	if ((i = sh_history_opt(av, opt)) < 0)
		return (1);
	j = 0;
	while (opt[j])
	{
/* 		if (opt[j] == 'a') */
/* 			sh_hist_append_w(av[i]); */
/* 		else if (opt[j] == 'n') */
/* 			sh_hist_append_r(av[i]); */
/* 		else if (opt[j] == 'r') */
/* 			sh_hist_read(av[i]); */
/* 		else if (opt[i] == 'w') */
/* 			sh_hist_write(av[i]); */
/* 		else if (opt[i] == 'c') */
/* 			sh_hist_clear(); */
/* 		else if (opt[i] == 'd') */
/* 			sh_hist_delete(av[i]); */
		j++;
	}
/* 	if (j == 0) */
/* 		sh_hist_disp(); */
	return (0);
}
