/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:07:44 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/05 20:12:26 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**		in that order:
**	brace expansion
**	tilde expansion
**	parameter and variable expansion
**	command substitution
**	arithmetic expansion
**	word splitting
**	filename expansion
*/

static int		sh_squote1(char **s, int i, int *j)
{
	i++;
	while ((*s)[i] && (*s)[i] != '\'')
		(*s)[(*j)++] = (*s)[i++];
	return (i);
}

static int		sh_dquote1(char **s, int i, int *j)
{
	char	quote;

	quote = (*s)[i];
	i++;
	while ((*s)[i] && (*s)[i] != quote)
	{
		if (((*s)[i] == '\\' && ((*s)[i + 1] == '\n' || (*s)[i + 1] == '\"'
					|| (*s)[i + 1] == '\\' || (*s)[i + 1] == '`')))
			i++;
		(*s)[(*j)++] = (*s)[i++];
	}
	return (i);
}

static char		*sh_rm_quote(char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'')
			i = sh_squote1(&s, i, &j);
		else if (s[i] == '\"' || s[i] == '`')
			i = sh_dquote1(&s, i, &j);
		else if (s[i] == '\\')
			s[j++] = s[++i];
		else
			s[j++] = s[i];
		s[i] ? i++ : 0;
	}
	ft_strclr(s + j);
	return (s);
}

static void		sh_del_void(t_token **prev, t_token **exp, t_token **lexer)
{
	if (*prev)
	{
		(*prev)->next = (*exp)->next;
		free((*exp)->lexeme);
		free(*exp);
		*exp = *prev;
	}
	else
	{
		*prev = (*exp)->next;
		free((*exp)->lexeme);
		free(*exp);
		*lexer = *prev;
		*exp = *prev;
	}
}

t_token			*sh_expansion(t_token *lexer)
{
	t_token	*exp;
	t_token	*prev;

	prev = NULL;
	exp = lexer;
	while (exp)
	{
		exp->lexeme = sh_exp_tilde(exp->lexeme);
		while (sh_count_b(exp->lexeme))
		{
			sh_cmd_sub(&exp);
			exp = sh_word_split(&exp);
			if (!exp->lexeme || !exp->lexeme[0])
				sh_del_void(&prev, &exp, &lexer);
		}
		if (!g_signal || g_signal == SIGWINCH)
			exp->lexeme = sh_rm_quote(exp->lexeme);
		prev = exp;
		exp = exp->next;
	}
	return (lexer);
}
