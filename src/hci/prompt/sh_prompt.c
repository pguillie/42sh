/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:43:42 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/22 11:07:48 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prompt(int mode)
{
	char	*ps;

	if (mode == 1)
	{
		if (!(ps = sh_getvar("PS1")))
			ps = PS1;
	}
	else if (mode == 2)
	{
		if (!(ps = sh_getvar("PS2")))
			ps = PS2;
	}
	else if (mode == 3)
	{
		if (!(ps = sh_getvar("PS3")))
			ps = PS3;
	}
	else if (mode == 4)
	{
		if (!(ps = sh_getvar("PS4")))
			ps = PS4;
	}
	else
		return (0);
	return (sh_print_prompt(ps));
}
