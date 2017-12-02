/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_able.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:06 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:53:12 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_del_able(char *esc, t_line *line)
{
	return (esc[1] == '[' && esc[2] == '3' && esc[3] == '~'
		&& line->cur != line->used);
}
