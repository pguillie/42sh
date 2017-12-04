/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_host.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:47:08 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 16:28:52 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_host(char buff[], int *b, char h, int *len)
{
	char	host[128];
	int		i;

	if (gethostname(host, 128) == 0)
	{
		i = 0;
		while (host[i])
		{
			if (host[i] == '.' && h == 'h')
				break ;
			*len = (host[i] == '\n' ? 0 : *len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = host[i++];
		}
	}
	return (*len);
}
