/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_verification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:37 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/05 01:21:29 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_syn_err(char *lexeme)
{
	ft_putstr_fd("Syntax error near unexpected token `", 2);
	ft_putstr_fd(lexeme, 2);
	ft_putstr_fd("\'\n", 2);
	return (SYN_ERR);
}

static int	sh_parse_sub(t_token *lex)
{
	size_t	i;
	int		bracket;

	i = 0;
	bracket = 0;
	if (lex->category <= SUB_SHELL && lex->next->category == SUB_SHELL)
		return (sh_syn_err(lex->lexeme));
	if (lex->category == SUB_SHELL && lex->next->category <= SUB_SHELL)
		return (sh_syn_err(lex->next->lexeme));
	while (lex->lexeme[i])
	{
		if (lex->lexeme[i] == '\\')
			i++;
		else
		{
			if (lex->lexeme[i] == '(')
				bracket++;
			if (lex->lexeme[i] == ')')
				bracket--;
		}
		i++;
	}
	if (bracket)
		return (sh_syn_err(")"));
	return (0);
}

int			sh_verification(t_token *lex, int ret)
{
	if (!lex)
		return (ret);
	if (lex->category > NEWLINE || lex->category == PIPE)
		return (sh_syn_err(lex->lexeme));
	while (lex->next)
	{
		if (lex->category == REDIRECTION)
		{
			if (lex->next->category != FILDES && lex->next->category != HEREDOC)
				return (sh_syn_err(lex->next->category == NEWLINE ?
							"newline" : lex->next->lexeme));
		}
		if (lex->category >= PIPE)
			if (lex->next->category > NEWLINE || lex->next->category == PIPE)
				return (sh_syn_err(lex->next->lexeme));
		if (sh_parse_sub(lex))
			return (SYN_ERR);
		lex = lex->next;
	}
	return (ret);
}
