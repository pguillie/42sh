/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:57:55 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:57:57 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_cmd_del(t_cmd **cmd)
{
	size_t	i;

	ft_strtabdel((*cmd)->av);
	i = 0;
	while (i < (*cmd)->nb_redir)
	{
		ft_strdel(&((*cmd)->redir[i].type));
		ft_strdel(&((*cmd)->redir[i].right));
		i++;
	}
	ft_memdel((void**)&(*cmd)->redir);
	ft_memdel((void**)cmd);
}
