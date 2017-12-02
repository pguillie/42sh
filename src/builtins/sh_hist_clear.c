/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:31:04 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 21:32:08 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hist_clear(void)
{
	int		fd;

	if ((fd = open(sh_getvar("HISTFILE"), O_TRUNC)) >= 0)
		close(fd);
}
