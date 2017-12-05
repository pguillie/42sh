/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_count_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:06:40 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/05 19:16:00 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_squote(char *s, int y)
{
	int i;

	i = y;
	s[i] ? i++ : 0;
	while (s[i] && s[i] != '\'')
	{
		if (s[i] == '\'')
			break ;
		i++;
	}
	return (!s[i] ? y : ++i);
}

static int	sh_dquote(char *s, int i, int *cpt)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
	{
		if ((s[i] == '\\' && (s[i + 1] == '\n'
				|| s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '`')))
			i++;
		else if (s[i] == '`')
			*cpt += 1;
		i++;
	}
	return (i);
}

int			sh_count_b(char *s)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i = sh_squote(s, i);
		else if (s[i] == '\"')
			i = sh_dquote(s, i, &cpt);
		else if (s[i] == '\\')
			i++;
		else if (s[i] == '`')
			cpt++;
		s[i] ? i++ : 0;
	}
	return (cpt / 2);
}
