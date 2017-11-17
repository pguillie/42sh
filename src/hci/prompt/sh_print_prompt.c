/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:43:47 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/16 15:43:48 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_print_prompt(char *ps)
{
	char	buff[PRT_SIZE + 1];
	int		p;
	int		b;
	int		len;

	bzero(buff, PRT_SIZE + 1);
	p = 0;
	b = 0;
	len = 0;
	while (ps[p])
	{
		if (ps[p] == '\\' && (p += 1))
			p += sh_prompt_conv(ps + p, buff, &b, &len);
		else
		{
			if (b == PRT_SIZE)
				b = ft_flush_buff(buff, PRT_SIZE);
			buff[b++] = ps[p++];
			len += 1;
		}
	}
	ft_flush_buff(buff, PRT_SIZE);
	return (len);
}
