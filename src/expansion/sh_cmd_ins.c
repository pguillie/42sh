/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:14:05 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/05 18:33:17 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_cmd_ins(t_token *exp, char *cmd, int l, int j)
{
	char	*tmp;
	char	*res;

	while (exp->lexeme[l] && exp->lexeme[l] != '`'
		&& (!l || exp->lexeme[l - 1] != '\\'))
		l++;
	tmp = ft_strndup(exp->lexeme, l);
	res = ft_strjoin(tmp, cmd);
	tmp ? free(tmp) : 0;
	tmp = res;
	res = ft_strjoin(tmp, exp->lexeme + l + j + (j == 0 ? 2 : 1));
	free(exp->lexeme);
	exp->lexeme = res;
	free(tmp);
	return (l + ft_strlen(cmd));
}
