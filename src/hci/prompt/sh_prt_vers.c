/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_vers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:52:53 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/16 16:10:26 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_prt_vers(char buff[], int *b, char r)
{
	char	*version;
	int		dot;
	int		i;

	version = sh_getvar("42SH_VERSION");
	i = 0;
	dot = 0;
	while (version[i])
	{
		if (version[i] == '.')
		{
			dot += 1;
			if (r == 'v' && dot == 2)
				break ;
		}
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = version[i++];
	}
	return (i);
}
