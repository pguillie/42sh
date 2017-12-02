/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:06:06 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 16:44:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_histexp_line(t_line *hist, int offset)
{
	if (offset == 0)
		return (NULL);
	if (offset < 0)
	{
		while (hist->down)
			hist = hist->down;
		while (offset && hist->up)
		{
			hist = hist->up;
			offset++;
		}
	}
	else
	{
		while (hist->up)
			hist = hist->up;
		while (--offset && hist->down)
			hist = hist->down;
	}
	if (offset || !hist->down)
		return (NULL);
	return (ft_strdup(hist->str));
}
