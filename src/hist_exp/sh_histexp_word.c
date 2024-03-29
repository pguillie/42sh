/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:47:54 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/01 13:51:53 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_histexp_error(char *str, int i)
{
	str[i] = 0;
	return (ft_error(SHELL, str, "Bad word specifier"));
}

static char	*sh_histexp_wdollar(t_token *w)
{
	int size;

	size = sh_list_len(w) - 1;
	return (sh_histexp_new(w, size, size));
}

static int	sh_histexp_word_norme(char *new, char *str, int i, char **exp)
{
	free(*exp);
	*exp = new;
	ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	return (0);
}

int			sh_histexp_word(char *str, int i, char **exp)
{
	t_token *word;
	char	*new;
	int		j[2];

	word = NULL;
	if (!(j[1] = 1) || !*exp || sh_lexer(&word, *exp) < 0)
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
