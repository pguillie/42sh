/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:46:00 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:46:01 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_exit(char *av[], int ret)
{
	if (av && av[1])
	{
		if (av[2])
			return (ft_error(av[0], E_2MNARG, NULL));
		ret = ft_atoi(av[1]);
	}
	ft_putendl("exit");
	exit(ret);
}
