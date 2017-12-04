/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:04:24 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/04 15:41:32 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_unsetenv(char **av)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (av[i])
	{
		if (ft_strequ(av[i], "PATH"))
			sh_unsetvar("PATH", 0, 0);
		else if (ft_strchr(av[i], '='))
			ret = 1;
		else if (sh_unsetvar(av[i], V_EXPORT, 0) < 0)
			return (-1);
		i++;
	}
	return (ret);
}
