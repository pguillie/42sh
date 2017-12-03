/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_tab_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:57:16 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/03 18:05:01 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_count_len(char *str, int i)
{
	int len;

	len = 0;
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

static int	sh_squote(char *str, int *t)
{
	int		first;
	int		i;

	first = 0;
	i = *t;
	while (str[i])
	{
		if (!first && (str[i] == '\"' || str[i] == '\''))
			first = str[i];
		else if (str[i] == first)
			first = 0;
		if (str[i] == '`' && first == '\'')
		{
			*t = i;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	sh_count_b(char *str)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		else if (str[i] == '`')
			cpt++;
		i++;
	}
	return (cpt / 2);
}

char	**sh_only_tab_b(char *str)
{
	char	**tmp;
	int	t;
	int	i;
	int	tt;

	i = 0;
	t = -1;
	if (!(tmp = (char**)ft_memalloc(sizeof(char*) * sh_count_b(str) + 1)))
		return (NULL);
	while (str[i])
	{
		if (!sh_squote(str, &i))
		{
			while (str[i])
			{
				if (str[i] == '\\' && str[i + 1])
					i++;
				else if (str[i] == '`')
					break ;
				i++;
			}
			if (str[i])
			{
			if (!(tmp[++t] = ft_strnew(sh_count_len(str, i) + 1)))
			{
				ft_strtabdel(tmp);
				return (NULL);
			}
			tt = 0;
			while (str[i])
			{
				if (str[i] == '\\' && str[i + 1] == '`')
					i++;
				else if (str[i] == '`')
					break ;
				i++;
			}
			tmp[t][tt++] = str[++i];
			while (str[++i])
			{
				if (str[i] == '\\' && str[i + 1] == '`')
					i++;
				else if (str[i] == '`')
					break ;
				tmp[t][tt++] = str[i];
			}
			tmp[t][tt++] = '\n';
			}
		}
		str[i] ? i++ : 0;
	}
	tmp[++t] = NULL;
	return (tmp);
}
