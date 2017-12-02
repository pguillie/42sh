/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hline_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:55:27 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 22:05:52 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line	*sh_hline_new(char *str, t_line *up)
{
	t_line	*new;

	if (!(new = (t_line*)ft_memalloc(sizeof(t_line))))
		return (NULL);
	new->capacity = ((ft_strlen(str) + 1) / BUFF_SIZE + 1) * BUFF_SIZE;
	if (!(new->str = ft_strnew(new->capacity)))
	{
		free(new);
		return (NULL);
	}
	ft_strcat(new->str, str);
	new->used = ft_strlen(str);
	new->cur = 0;
	new->up = up;
	new->down = NULL;
	return (new);
}
