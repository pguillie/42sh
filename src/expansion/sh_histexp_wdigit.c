/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_wdigit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:08:48 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 11:08:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_histexp_wdigit(t_token *w, char *str, int *i)
{
	int	j;
	int	one;
	int	two;

	one = 0;
	while (ft_isdigit(str[*i]))
		one = one * 10 + str[(*i)++] - '0';
	two = one;
	if (str[*i] == '*' && ++(*i))
		return (sh_histexp_new(w, one, -1));
	j = *i;
	if (str[*i] == '-' && ++(*i))
	{
		if ((str[*i] == '$' || str[*i] == '*') && ++(*i))
			return (sh_histexp_new(w, one, -1));
		two = 0;
		while (ft_isdigit(str[*i]))
			two = two * 10 + str[(*i)++] - '0';
		if (*i == j + 1)
			return (sh_histexp_new(w, one, -2));
	}
	return (sh_histexp_new(w, one, two));
}
