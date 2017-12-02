/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:32:12 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 13:46:27 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_histexp_quote2(char *exp, char c, int size)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = (char*)ft_memalloc(size)))
		return (NULL);
	i = 0;
	j = 1;
	new[0] = '\'';
	while (exp[i])
	{
		if ((c == 'x' && (exp[i] == ' ' || exp[i] == '\t' || exp[i] == '\n'))
				|| exp[i] == '\'')
			new[j++] = '\'';
		if (exp[i] == '\'')
			new[j++] = '\\';
		new[j++] = exp[i];
		if ((c == 'x' && (exp[i] == ' ' || exp[i] == '\t' || exp[i] == '\n'))
				|| exp[i] == '\'')
			new[j++] = '\'';
		i++;
	}
	new[j] = '\'';
	return (new);
}

char		*sh_histexp_quote(char *exp, char c)
{
	int		word;
	int		quote;
	int		i;

	word = 1;
	quote = 0;
	i = 0;
	while (exp[i])
	{
		if (c == 'x' && (exp[i] == ' ' || exp[i] == '\t' || exp[i] == '\n'))
			word++;
		if (exp[i] == '\'')
			quote++;
		i++;
	}
	return (sh_histexp_quote2(exp, c, i + (word * 3) + (quote * 4)));
}
