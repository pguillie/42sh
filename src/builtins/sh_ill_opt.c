/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ill_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:35:05 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/27 14:36:01 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ill_opt(char *fct, char opt, char *usage)
{
	ft_putstr_fd(fct, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(opt, 2);
	ft_putchar_fd('\n', 2);
	if (usage)
		ft_putendl_fd(usage, 2);
	return (1);
}
