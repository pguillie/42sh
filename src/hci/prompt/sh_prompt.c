/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:43:42 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 17:04:08 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prompt(int mode)
{
	char	*ps;

	ps = NULL;
	if (mode == 1)
		ps = sh_getvar("PS1");
	else if (mode == 2)
		ps = sh_getvar("PS2");
	else if (mode == 3)
		ps = sh_getvar("PS3");
	else if (mode == 4)
		ps = sh_getvar("PS4");
	if (!ps)
		return (0);
	return (sh_print_prompt(ps));
}
