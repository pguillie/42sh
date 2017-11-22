/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:51:44 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/21 15:48:26 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_setenv(char **av)
{
	int		i;
	int		ret[2];

	ret[0] = 0;
	i = 1;
	while (av[i])
	{
		if ((ret[1] = sh_setvar(av[i], NULL, V_EXPORT)) < 0)
			return (-1);
		else if (ret[1] > 1)
			ret[0] = ft_error(av[0], av[i], "Not a valid identifier");
		i++;
	}
	return (ret[0]);
}
