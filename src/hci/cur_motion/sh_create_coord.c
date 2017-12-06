/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_coord.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:52:08 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/06 16:52:19 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_coord_prompt(struct winsize w, t_coord *cur, size_t prompt)
{
	size_t	i;

	cur->x = 0;
	cur->y = 0;
	i = 0;
	while (i < prompt)
	{
		if (++(cur->x) == w.ws_col)
		{
			cur->x = 0;
			cur->y += 1;
		}
		i++;
	}
}

t_coord		*sh_create_coord(t_line *line, size_t prompt)
{
	struct winsize	w;
	t_coord			*new;
	t_coord			cur;
	size_t			i;

	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (NULL);
	if (!(new = (t_coord*)ft_memalloc(sizeof(t_coord) * (line->used + 2))))
		return (NULL);
	sh_coord_prompt(w, &cur, prompt);
	i = 0;
	while (i <= line->used)
	{
		new[i].x = cur.x;
		new[i].y = cur.y;
		if (++cur.x == w.ws_col || line->str[i] == '\n')
		{
			cur.x = 0;
			cur.y += 1;
		}
		i++;
	}
	new[i].x = w.ws_col;
	new[i].y = -1;
	return (new);
}
