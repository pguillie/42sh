/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:09 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:53:11 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ctrl_d(t_line *line, char *save)
{
	if (line->str[line->cur])
		return (sh_del_r(line));
	else if (line->cur == 0 && !save)
		return (EOT);
	return (0);
}
