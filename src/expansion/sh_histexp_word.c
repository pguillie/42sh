/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:09:23 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/07 16:36:18 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		sh_histexp_error(char *str, int i)
{
	str[i] = 0;
	return (ft_error(SHELL, str, "Bad word specifier"));
}

static char		*sh_histexp_wdollar(t_token *w)
{
	int size;

	size = sh_list_len(w) - 1;
	return (sh_histexp_new(w, size, size));
}

static int		sh_histexp_word_norme(char *new, char *str, int i, char **exp)
{
	free(*exp);
	*exp = new;
	ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	return (0);
}

static t_token	*sh_histexp_lex(char **exp)
{
	t_token	*word;
	char	*str;

	if (!(str = ft_strjoin(*exp, "\n")))
		return (NULL);
	word = NULL;
	if (sh_lexer(&word, &str) < 0)
	{
		sh_token_del(&word);
		word = NULL;
	}
	free(str);
	return (word);
}

int				sh_histexp_word(char *str, int i, char **exp)
{
	t_token	*word;
	char	*new;
	int		j[2];

	j[1] = 1;
	if (!(word = sh_histexp_lex(exp)))
		return (1);
	new = NULL;
	j[0] = (str[i] == ':' ? i++ : i);
	if (str[i] == '^')
		new = sh_histexp_wcaret(word, str, &i);
	else if (str[i] == '%' && ++i)
		new = ft_strdup(*sh_wmatch());
	else if (str[i] == '$' && ++i)
		new = sh_histexp_wdollar(word);
	else if (str[i] == '*' && ++i)
		new = sh_histexp_new(word, 1, -1);
	else if ((str[j[0]] == ':' && ft_isdigit(str[i])) || str[i] == '-')
		new = sh_histexp_wdigit(word, str, &i);
	else
		j[1] = 0;
	sh_token_del(&word);
	if ((!new && j[1]) || !j[1])
		return (j[1] ? sh_histexp_error(str + j[0], i) : 0);
	return (sh_histexp_word_norme(new, str + j[0], i - j[0], exp));
}
