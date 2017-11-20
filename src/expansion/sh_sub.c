/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:23:40 by pbourlet          #+#    #+#             */
/*   Updated: 2017/11/17 16:03:02 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_epu_sub(t_token **exp)
{
	t_token	*cur;

	cur = *exp;
	free(cur->lexeme);
	cur->lexeme = ft_strdup("");
	cur = cur->next;
	while (cur && !ft_strequ(cur->lexeme, ")"))
		cur = cur->next;
	cur = NULL;
	return (0);
}

int		sh_sub(t_token **exp)
{
	int		stat;
	pid_t	child;
	t_cmd	***cmd_list;
	int		*op;
	int		ret;

	ft_printf("exp:%s\n", (*exp)->lexeme);
	sh_epu_sub(exp);
	*exp = (*exp)->next;
	ft_printf("exp:%s\n", (*exp)->lexeme);
	ret = 0;
	op = NULL;
	cmd_list = NULL;
	child = fork();
	if (child == 0)
	{
		sh_parser(sh_expansion(*exp), &cmd_list, &op);
		stat = sh_list_browse(cmd_list, op, ret);
		exit(1);
	}
	else
		waitpid(child, &stat, 0);
	while (*exp && !ft_strequ((*exp)->lexeme, ")"))
		*exp = (*exp)->next;
	if (ft_strequ((*exp)->lexeme, ")"))
		*exp = (*exp)->next;
	ft_printf("lex:%s\n", (*exp)->lexeme);
	return (0);
}
