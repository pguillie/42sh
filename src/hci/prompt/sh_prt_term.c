/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:48:58 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 16:40:19 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_term(char buff[], int *b, int *len)
{
	char	*term;
	int		i;
	int		n;

	if ((term = ttyname(0)))
	{
		i = 0;
		n = 0;
		while (term[i])
			if (term[i++] == '/')
				n = i;
		while (term[n])
		{
			*len = (term[n] == '\n' ? 0 : *len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = term[n++];
		}
	}
	return (*len);
}
