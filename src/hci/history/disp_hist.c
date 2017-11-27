/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:03:23 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/24 14:02:07 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	disp_hist_tmp(void)
{
	t_hist		**state;
	int			i;

	i = 1;
	state = global_hist();
	printf("\n===== HIST =====\n");
	printf("---STATE---\n");
	printf("offset: %d\n", (*state)->offset);
	printf("lengh: %d\n", (*state)->length);
	printf("size  : %d\n", (*state)->size);
	printf("---ENTRY---\n");
	while ((*state)->length != i - 1)
	{
		printf("time: %10d --  ", (*state)->entry[i].timestamp);
		printf("line: %s\n", (*state)->entry[i++].line);
	}
	printf("===================\n");
}
