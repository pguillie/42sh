/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_printenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:49:00 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:49:01 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_printenv(char *var)
{
	extern char **environ;
	char		*val;
	int			i;

	if (var)
	{
		if ((val = getenv(var)))
			ft_putendl(val);
		else
			return (1);
	}
	else if (environ)
	{
		i = 0;
		while (environ[i])
			ft_putendl(environ[i++]);
	}
	return (0);
}
