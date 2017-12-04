/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:49:13 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 16:41:49 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_time(char buff[], int *b, char c, int *len)
{
	time_t		t;

	t = time(NULL);
	if (t >= 0)
	{
		if (c == 't')
			*len = sh_prt_strftime(buff, b, "%H:%M:%S", len);
		else if (c == 'T')
			*len = sh_prt_strftime(buff, b, "%I:%M:%S", len);
		else if (c == '@')
			*len = sh_prt_strftime(buff, b, "%I:%M %p", len);
		else if (c == 'A')
			*len = sh_prt_strftime(buff, b, "%H:%M", len);
	}
	return (*len);
}
