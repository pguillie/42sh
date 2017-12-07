/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tab_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:12:21 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/07 16:21:53 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_tab_builtin_norme(char **array[])
{
	size_t	len;

	len = ft_strlen(*array[0]);
	if (ft_strnequ(*array[0], "history", len))
		sh_tab_append(array, "history", 0);
	if (ft_strnequ(*array[0], "printenv", len))
		sh_tab_append(array, "printenv", 0);
	if (ft_strnequ(*array[0], "readonly", len))
		sh_tab_append(array, "readonly", 0);
	if (ft_strnequ(*array[0], "setenv", len))
		sh_tab_append(array, "setenv", 0);
	if (ft_strnequ(*array[0], "unset", len))
		sh_tab_append(array, "unset", 0);
	if (ft_strnequ(*array[0], "unsetenv", len))
		sh_tab_append(array, "unsetenv", 0);
}

void		sh_tab_builtin(char **array[])
{
	size_t	len;

	len = ft_strlen(*array[0]);
	if (ft_strnequ(*array[0], "cd", len))
		sh_tab_append(array, "cd", 0);
	if (ft_strnequ(*array[0], "declare", len))
		sh_tab_append(array, "declare", 0);
	if (ft_strnequ(*array[0], "echo", len))
		sh_tab_append(array, "echo", 0);
	if (ft_strnequ(*array[0], "env", len))
		sh_tab_append(array, "env", 0);
	if (ft_strnequ(*array[0], "exit", len))
		sh_tab_append(array, "exit", 0);
	if (ft_strnequ(*array[0], "export", len))
		sh_tab_append(array, "export", 0);
	sh_tab_builtin_norme(array);
}
