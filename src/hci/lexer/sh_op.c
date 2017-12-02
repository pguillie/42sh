/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:40 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:56:49 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ctrl_op(char *str)
{
	if (ft_strnequ(str, ";;&", 3))
		return (3);
	if (ft_strnequ(str, "||", 2) || ft_strnequ(str, "&&", 2)
			|| ft_strnequ(str, ";;", 2) || ft_strnequ(str, ";&", 2)
			|| ft_strnequ(str, "|&", 2))
		return (2);
	if ((str[0] == '&') || str[0] == ';' || str[0] == '|' || str[0] == '('
			|| str[0] == ')' || str[0] == '\n')
		return (1);
	return (0);
}

int		sh_rdir_op(char *str)
{
	if (ft_strnequ(str, "&>>", 3) || ft_strnequ(str, "<<<", 3))
		return (3);
	if (ft_strnequ(str, "&>", 2) || ft_strnequ(str, ">&", 2)
			|| ft_strnequ(str, ">|", 2) || ft_strnequ(str, ">>", 2)
			|| ft_strnequ(str, "<<", 2) || ft_strnequ(str, "<&", 2)
			|| ft_strnequ(str, "<>", 2))
		return (2);
	if (str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}
