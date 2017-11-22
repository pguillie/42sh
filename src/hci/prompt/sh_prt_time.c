/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:49:13 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/22 12:11:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_time(char buff[], int *b, char c)
{
	struct tm	*tm;
	time_t		t;
	int			len;

	len = 0;
	t = time(NULL);
	if (t >= 0 && (tm = localtime(&t)))
	{
		if (c == 't')
			len = sh_prt_strftime(buff, b, "%H:%M:%S", tm);
		else if (c == 'T')
			len = sh_prt_strftime(buff, b, "%I:%M:%S", tm);
		else if (c == '@')
			len = sh_prt_strftime(buff, b, "%I:%M %p", tm);
		else if (c == 'A')
			len = sh_prt_strftime(buff, b, "%H:%M", tm);
	}
	return (len);
}
