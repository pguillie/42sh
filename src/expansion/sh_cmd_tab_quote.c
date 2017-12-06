/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_tab_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:57:16 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/06 18:57:27 by pbourlet         ###   ########.fr       */
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

static char	*sh_cmd_cpy(char *str, int *i, int len)
{
	char	*tmp;
	int		tt;

	tt = 0;
	tmp = NULL;
	while (str[*i] && str[*i] != '`')
	{
		if (str[*i] == '\\' && str[*i + 1])
			(*i)++;
		(*i)++;
	}
	if (str[*i] == '`')
		(*i)++;
	if (!(tmp = ft_strnew(len - 1)))
		return (NULL);
	if (len > 2)
	{
		while (len-- > 2)
			tmp[tt++] = str[(*i)++];
		tmp[tt] = '\n';
	}
	return (tmp);
}

char		**sh_cmd_tab_quote(char *str)
{
	char	**array;
	int		i;
	int		t;
	int		len;

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
			if (!(array[t++] = sh_cmd_cpy(str, &i, len)))
				return (NULL);
		i += str[i] == '\\' ? 2 : 0;
		str[i] ? i++ : 0;
	}
	array[t] = NULL;
	return (array);
}
