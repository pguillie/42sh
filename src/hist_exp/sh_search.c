/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:16:35 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/30 16:03:02 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_search(char *str, int l, t_hist *hist)
{
	int		offset;
	char	save;

	save = 0;
	offset = hist->offset - 1;
	if (str[0] == '?')
	{
		if (str[l] == '?' && (save = 1))
			str[l] = '\0';
		while (offset && !ft_strstr(hist->entry[offset].line, str + 1))
			offset--;
		str[l] = save ? '?' : 0;
	}
	else
		while (offset && !ft_strnequ(hist->entry[offset].line, str, l))
			offset--;
	if (!offset)
		return (NULL);
	return (sh_histexp_line(offset + 1));
}
