/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:14:05 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/04 17:22:25 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_cmd_ins(char *lexeme, char *str, int *i)
{
	char	*tmp;
	char	*res;
	int		y;

	y = 0;
	while (lexeme[i[3]] && lexeme[i[3]] != '`')
		i[3]++;
	tmp = ft_strndup(lexeme, i[3]);
	res = ft_strjoin(tmp, str);
	tmp ? free(tmp) : 0;
	if ((!tmp && i) || !res)
	{
		free(res);
		return (NULL);
	}
	tmp = res;
	res = ft_strjoin(tmp, lexeme + i[3] + i[4] + 1);
	free(tmp);
	return (res);
}
