/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sub_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:37:56 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/07 13:45:15 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_small_main(char *cmd)
{
	t_token	*lexer;
	t_cmd	***cmd_list;
	int		*op;
	int		ret;

	ret = 0;
	lexer = NULL;
	cmd_list = NULL;
	op = NULL;
	if ((ret = sh_lexer(&lexer, &cmd)) < 0 || ret & LEX_LOOP)
	{
		if (ret & LEX_LOOP)
			ft_error(SHELL, "Syntax error", NULL);
		ret = -1;
	}
	else if (sh_verification(lexer, 0))
		return (258);
	else if (sh_parser(sh_expansion(lexer), &cmd_list, &op) < 0)
		ret = -1;
	else if ((ret = sh_list_browse(cmd_list, op, ret)) < 0)
		ret = -1;
	lexer ? sh_token_del(&lexer) : 0;
	cmd_list ? sh_list_del(&cmd_list, &op) : 0;
	return (ret);
}

int		sh_sub_shell(char *cmd)
{
	pid_t	child;
	int		ret;

	ret = 0;
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		cmd[ft_strlen(cmd) - 1] = '\n';
		exit(sh_small_main(cmd + 1));
	}
	return (sh_wait(child, ret));
}
