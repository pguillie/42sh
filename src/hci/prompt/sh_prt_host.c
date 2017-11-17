/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_host.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:47:08 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/16 15:47:09 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_host(char buff[], int *b, char h)
{
	char	host[128];
	int		i;
	int		len;

	len = 0;
	if (gethostname(host, 128) == 0)
	{
		i = 0;
		while (host[i])
		{
			if (host[i] == '.' && h == 'h')
				break ;
			len = (host[i] == '\n' ? 0 : len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = host[i++];
		}
	}
	return (len);
}
