/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:49:38 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/16 15:49:39 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_user(char buff[], int *b)
{
	struct passwd	*p;
	int				i;

	i = 0;
	if ((p = getpwuid(getuid())))
	{
		while (p->pw_name[i])
		{
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = p->pw_name[i++];
		}
	}
	return (i);
}
