/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:30:36 by pbourlet          #+#    #+#             */
/*   Updated: 2017/11/30 16:28:23 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	sh_isok(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '=' || c == '(')
		return (1);
	return (0);
}

int			sh_histexp_id(char *str, int i)
{
	char	quote;

	quote = 0;
	while (str && str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		else if (str[i] == quote)
			quote = 0;
		else if (str[i] == '\'' && !quote)
			quote = str[i];
		else if (str[i] == '!' && !sh_isok(str[i + 1]) && !quote)
			return (i);
		i++;
	}
	return (-1);
}
