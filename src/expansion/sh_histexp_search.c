/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:12:18 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 17:24:22 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_histexp_search(char *str, int l, t_line *hist)
{
	int		save;

	hist = hist->up;
	save = 0;
	if (str[0] == '?')
	{
		if (str[l] == '?' && (save = 1))
			str[l] = '\0';
		while (hist && !ft_strstr(hist->str, str + 1))
			hist = hist->up;
		str[l] = save ? '?' : 0;
	}
	else
		while (hist && !ft_strnequ(hist->str, str, l))
			hist = hist->up;
	if (!hist)
		return (NULL);
	return (ft_strdup(hist->str));
}
