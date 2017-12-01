/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:43:16 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/01 15:56:52 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_hist_move(char move)
{
	t_hist	**hist;

	if (!(hist = global_hist()))
		return (NULL);
	if (move == '-' && (*hist)->offset > 0)
		(*hist)->offset--;
	else if (move == '+' && (*hist)->offset < (*hist)->length)
		(*hist)->offset++;
	return ((*hist)->entry[(*hist)->offset].line);
}
