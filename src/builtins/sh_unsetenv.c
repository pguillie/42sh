/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:04:24 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/03 13:37:28 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_unsetenv(char **av)
{
	int		i;
	int		ret[2];

	ret[0] = 0;
	i = 0;
	while (av[i])
	{
		if (ft_strequ(av[i], "PATH"))
			sh_unsetvar("PATH", 0, 0);
		else if (ft_strchr(av[i], '='))
			ret[0] = 1;
		else if ((ret[1] = sh_unsetvar(av[i], V_EXPORT, 0)) < 0)
			return (-1);
		else if (ret[1] > 1)
			ret[0] = ft_error(av[0], av[i], "Not a valid identifier");
		i++;
	}
	return (ret[0]);
}
