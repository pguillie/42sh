/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:39 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:56:49 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_token_del(t_token **begin)
{
	t_token	*tmp;

	if (*begin)
	{
		while (*begin)
		{
			tmp = (*begin)->next;
			ft_strdel(&(*begin)->lexeme);
			free(*begin);
			*begin = NULL;
			*begin = tmp;
		}
	}
	return (-1);
}
