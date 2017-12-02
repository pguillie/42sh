/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:39 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:56:49 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_token_new(t_token **list, char *lexeme, int category)
{
	t_token	*new;
	t_token	*l;

	if (!(new = (t_token*)ft_memalloc(sizeof(t_token))))
		return (-1);
	new->lexeme = lexeme;
	new->category = category;
	new->next = NULL;
	if (*list)
	{
		l = *list;
		while (l->next)
			l = l->next;
		l->next = new;
	}
	else
		*list = new;
	return (0);
}
