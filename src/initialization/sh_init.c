/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:57:36 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:57:36 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_init(t_tc *init)
{
	if (sh_init_var() < 0)
		return (-1);
	if (sh_init_termcaps(init))
		ft_error("Warning", "Line edition can't switch to advanced mode", NULL);
	sh_hash_init();
	return (0);
}
