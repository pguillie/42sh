/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_tab_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:57:16 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/05 19:54:27 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_count_len(char *str, int i)
{
	int len;

	len = 0;
	while (str[i] && str[i] != '`')
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		i++;
	}
	if (str[i])
	{
		len = 1;
		while (str[i + len] && str[i + len] != '`')
		{
			if (str[i + len] == '\\' && str[i + len + 1])
				len++;
			len++;
		}
		if (str[i + len] == '`' && str[i + len - 1] != '\\')
			len++;
	}
	return (len);
}

char	**sh_cmd_tab_quote(char *str)
{

	char	**array;
	int		i;
	int		t;
	int		len;
	int		tt;

	t = 0;
	i = 0;
	if (!(array = (char**)ft_memalloc(sizeof(char*) * (sh_count_b(str) + 1))))
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			i++;
		if (str[i] == '\'')
			i = sh_squote(str, i);
		if (str[i] && (len = sh_count_len(str, i)))
		{
			tt = 0;
			while (str[i] && str[i] != '`')
			{
				if (str[i] == '\\' && str[i + 1])
					i++;
				i++;
			}
			if (str[i] == '`')
				i++;
			if (!(array[t] = ft_strnew(len - 1)))
			{
				ft_strtabdel(array);
				return (NULL);
			}
			if (len > 2)
			{
				while (len-- > 2)
					array[t][tt++] = str[i++];
				array[t][tt] = '\n';
			}
			t++;
		}
		i += str[i] == '\\' ? 2 : 0;
		str[i]  ? i++ : 0;
	}
	array[t] = NULL;
	return (array);
}
