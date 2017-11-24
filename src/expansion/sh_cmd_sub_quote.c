/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_sub_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:59:42 by pbourlet          #+#    #+#             */
/*   Updated: 2017/11/24 16:49:52 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_count_len(char *str)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (str[i] && str[i] != '`')
		i++;
	len++;
	i++;
	while (str[i] && str[i] != '`')
	{
		i++;
		len++;
	}
	return (len);
}

static int	sh_squote(char *str)
{
	int		i;
	int		first;

	first = 0;
	i = 0;
	while (str[i])
	{
		if (!first && (str[i] == '\"' || str[i] == '\''))
			first = str[i];
		else if (str[i] == first)
			first = 0;
		if (str[i] == '`' && first == '\'')
			return (1);
		i++;
	}
	return (0);
}

char		*sh_only_b(char *str)
{
	char	*tmp;
	int		i[2];

	ft_bzero(i, sizeof(int) * 2);
	if (sh_squote(str) || !(tmp = ft_strnew(sh_count_len(str) + 1)))
		return (NULL);
	while (str[i[0]])
	{
		if (str[i[0]] == '\\' && str[i[0] + 1] == '`')
			i[0]++;
		else if (str[i[0]] == '`')
			break ;
		i[0]++;
	}
	tmp[i[1]++] = str[++i[0]];
	while (str[++i[0]])
	{
		if (str[i[0]] == '\\' && str[i[0] + 1] == '`')
			i[0]++;
		else if (str[i[0]] == '`')
			break ;
		tmp[i[1]++] = str[i[0]];
	}
	tmp[i[1]] = '\n';
	return (tmp);
}
