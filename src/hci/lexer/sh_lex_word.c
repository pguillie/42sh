/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lex_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:44 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/03 11:12:23 by lcordier         ###   ########.fr       */
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

int			sh_lex_word(char *s)
{
	int		i;
	char	quote;
	int		bracket;

	i = 0;
	quote = 0;
	bracket = 0;
	while (s[i] && (quote || bracket || !sh_metachar(s[i])))
	{
		if (s[i] == '\\' && s[i + 1] && s[i + 1] != '\'')
			i++;
		else
		{
			if (s[i] == quote)
				quote = 0;
			else if ((s[i] == '\"' || s[i] == '\'' || s[i] == '`') && !quote)
				quote = s[i];
			else if (!quote && (bracket = sh_bracket(s, i, bracket)) < 0)
				return (i);
		}
		i++;
	}
	return (i);
}
