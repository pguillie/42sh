/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:14:05 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/04 12:29:40 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_boucle(char *lexeme, int i, int mode)
{
	while (lexeme[i])
	{
		sh_squote(lexeme, &i);
		if (lexeme[i])
		{
			if (lexeme[i] == '\\' && lexeme[i + 1])
				i += 1;
			else if (lexeme[i] == '`')
			{
				i += mode;
				break ;
			}
		}
		i += 1;
	}
	return (i);
}

char		*sh_cmd_ins(char *lexeme, char *str, int *i)
{
	char	*tmp;
	char	*res;
	int		y;

	y = 0;
	*i = sh_boucle(lexeme, *i, 0);
	tmp = ft_strndup(lexeme, *i);
	res = ft_strjoin(tmp, str);
	tmp ? free(tmp) : 0;
	if ((!tmp && i) || !res)
	{
		free(res);
		return (NULL);
	}
	y = *i;
	*i = sh_boucle(lexeme, (*i += 1), 1);
	tmp = res;
	res = ft_strjoin(tmp, lexeme + *i);
	if (!str)
		*i = y;
	free(tmp);
	return (res);
}
