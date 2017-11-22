/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:29:42 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/22 09:34:52 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_get_ptr_path(void)
{
	char	***varray;
	int		i;

	if ((varray = sh_var()))
	{
		i = 0;
		while ((*varray)[i])
		{
			if (ft_strnequ((*varray)[i] + 1, "PATH", 4)
					&& (*varray)[i][5] == '=')
				return ((*varray)[i]);
			i++;
		}
	}
	return (NULL);
}

void		sh_init_loop(t_token **lexer, t_cmd ****list, int **op)
{
	static char	*old_path = NULL;
	char		*new_path;

	new_path = sh_get_ptr_path();
	if (old_path != new_path)
	{
		old_path = new_path;
		sh_hash_free();
	}
	g_signal = 0;
	*lexer = NULL;
	*list = NULL;
	*op = NULL;
}
