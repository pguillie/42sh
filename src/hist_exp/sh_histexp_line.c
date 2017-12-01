/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:50:14 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/01 13:09:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_histexp_line(int offset)
{
	t_hist	**history;

	if (!(history = global_hist()) || offset == 0
			|| offset > (*history)->length)
		return (NULL);
	return (ft_strdup((*history)->entry[offset - 1].line));
}
