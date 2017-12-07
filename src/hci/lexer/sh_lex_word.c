/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lex_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:44 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/07 16:13:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_bracket(char *s, int i, int bracket)
{
	if (i > 0 && bracket == 0 && s[i] == '(')
		return (-1);
	if (i > 0 && !sh_metachar(s[i]) && s[i - 1] == ')')
		return (-1);
	if (s[i] == '(')
		bracket += 1;
	else if (s[i] == ')' && bracket > 0)
		bracket -= 1;
	return (bracket);
}

static int	sh_squote1(char *s, int i)
{
	i++;
	while (s[i] && s[i] != '\'')
		i++;
	return (i);
}

static int	sh_dquote1(char **s, int i)
{
	char	quote;

	quote = (*s)[i];
	i++;
	while ((*s)[i] && (*s)[i] != quote)
	{
		if ((*s)[i] == '\\' && (*s)[i + 1] == '\n')
			ft_memmove(*s + i, *s + i + 2, ft_strlen(*s + i + 2) + 1);
		else if ((*s)[i] == '\\' &&
				((*s)[i + 1] == '\"' || (*s)[i + 1] == '\\'
				|| (*s)[i + 1] == '`'))
			i++;
		i++;
	}
	return (i);
}

static int	sh_bslash(char **s, int i)
{
	if ((*s)[i + 1] == '\n')
		ft_memmove((*s) + i, (*s) + i + 2, ft_strlen(*s + i + 2) + 1);
	else
		i++;
	if (!(*s)[0])
		i++;
	return (i);
}

int			sh_lex_word(char **str, int t)
{
	int		i;
	int		bracket;
	char	*s;

	i = 0;
	s = *str + t;
	bracket = 0;
	while (s[i] && (bracket || !sh_metachar(s[i])))
	{
		if (s[i] == '\'')
			i = sh_squote1(s, i);
		else if (s[i] == '\"' || s[i] == '`')
			i = sh_dquote1(&s, i);
		else if (s[i] == '(' || s[i] == ')')
		{
			if ((bracket = sh_bracket(s, i, bracket)) < 0)
				return (i);
		}
		else if (s[i] == '\\')
			i = sh_bslash(&s, i);
		s[i] ? i++ : 0;
	}
	return (i);
}
