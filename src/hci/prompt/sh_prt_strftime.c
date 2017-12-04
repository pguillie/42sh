/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_strftime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:48:45 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 16:41:42 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_strftime(char buff[], int *b, char *format, int *len)
{
	char		date[128];
	int			i;
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	if (strftime(date, 128, format, tm) > 0)
	{
		i = 0;
		while (date[i])
		{
			*len = (date[i] == '\n' ? 0 : *len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = date[i++];
		}
	}
	return (*len);
}
