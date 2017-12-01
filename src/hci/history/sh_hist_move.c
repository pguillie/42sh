/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:24:32 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/01 17:24:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_hist_move(char move)
{
	t_hist	**hist;
	char	*tmp;

	if (!(hist = global_hist()))
		return (NULL);
	if (move == '-' && (*hist)->offset > 0)
		(*hist)->offset--;
	else if (move == '+' && (*hist)->offset < (*hist)->length)
		(*hist)->offset++;
	tmp = (*hist)->entry[(*hist)->offset].line;
	return (tmp);
}
