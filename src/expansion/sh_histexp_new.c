/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:07:00 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 12:09:17 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_histexp_new2(t_token *w, int i, int j, int size)
{
	char	*new;
	int		a;

	if (!(new = (char*)ft_memalloc(size)))
		return (NULL);
	a = -1;
	while (w)
	{
		++a;
		if (a >= i && (a <= j || j == -1 || (j == -2 && w->next)))
		{
			ft_strcat(new, w->lexeme);
			ft_strcat(new, (a == j || (j == -1 && !w->next)
							|| (j == -2 && (!w->next || !w->next->next))
							? "\0" : " "));
		}
		w = w->next;
	}
	return (new);
}

char		*sh_histexp_new(t_token *w, int i, int j)
{
	t_token	*t;
	int		a;
	int		size;

	a = -1;
	size = 0;
	t = w;
	while (t)
	{
		++a;
		if (a >= i && (a <= j || j == -1 || (j == -2 && t->next)))
			size += ft_strlen(t->lexeme) + 1;
		t = t->next;
	}
	if (i > a || (j >= 0 && (j > a || i > j)))
		return (NULL);
	return (sh_histexp_new2(w, i, j, size));
}
