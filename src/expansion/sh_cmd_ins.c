/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:14:05 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/05 04:53:28 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_cmd_ins(char *lexeme, char *str, int *i)
{
	char	*tmp;
	char	*res;

	while (lexeme[i[3]] && lexeme[i[3]] != '`')
		i[3]++;
	tmp = ft_strndup(lexeme, i[3]);
	res = ft_strjoin(tmp, str);
	tmp ? free(tmp) : 0;
	if ((!tmp && i[3]) || !res)
	{
		res ? free(res) : 0;
		return (NULL);
	}
	tmp = res;
	res = ft_strjoin(tmp, lexeme + i[3] + i[4] + 1);
	free(tmp);
	return (res);
}
