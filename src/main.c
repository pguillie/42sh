/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:05:30 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/07 15:03:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			main(void)
{
	t_tc	termcaps;
	t_token	*lexer;
	t_cmd	***cmd_list;
	int		*op;
	int		ret[2];

	if (sh_init(&termcaps))
		return (ft_error("Unable to initialize shell", NULL, NULL));
	ret[0] = 0;
	ret[1] = ERROR_MAX;
	sh_catch_signals();
	while (ret[1])
	{
		sh_init_loop(&lexer, &cmd_list, &op);
		if (sh_hci(&termcaps, &lexer, ret[0]))
			ret[1] -= 1;
		else if (sh_parser((lexer = sh_expansion(lexer)), &cmd_list, &op) < 0)
			ret[1] -= 1;
		else if ((ret[0] = sh_list_browse(cmd_list, op, ret[0])) < 0)
			ret[1] -= 1;
		lexer ? sh_token_del(&lexer) : 0;
		cmd_list ? sh_list_del(&cmd_list, &op) : 0;
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n");
	return (1);
}
