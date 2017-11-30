/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_list_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:30:46 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/29 16:31:57 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_list_len(t_token *list)
{
	int cpt;

	cpt = 0;
	while (list)
	{
		cpt++;
		list = list->next;
	}
	return (cpt);
}
