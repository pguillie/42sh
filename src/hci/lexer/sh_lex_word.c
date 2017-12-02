/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lex_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:44 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:56:49 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_lex_word(char *s)
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
			else if (s[i] == '(')
				bracket += 1;
			else if (s[i] == ')' && bracket > 0)
				bracket -= 1;
		}
		i++;
	}
	return (i);
}
