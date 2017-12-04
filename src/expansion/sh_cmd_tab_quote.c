/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_tab_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:57:16 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/04 16:03:12 by lcordier         ###   ########.fr       */
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

static int	sh_escape(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		else if (str[i] == '`')
			break ;
		i++;
	}
	return (i);
}

static char	*sh_norme(char *str, int *i)
{
	char	*tmp;
	int		tt;

	tt = 0;
	if (!(tmp = ft_strnew(sh_count_len(str, *i) + 1)))
		return (NULL);
	*i = sh_escape(str, *i);
	tmp[tt++] = str[++*i];
	while (str[++*i])
	{
		if (str[*i] == '\\' && str[*i + 1] == '`')
			*i += 1;
		else if (str[*i] == '`')
			break ;
		tmp[tt++] = str[*i];
	}
	tmp[tt++] = '\n';
	return (tmp);
}

char		**sh_only_tab_b(char *str)
{
	char	**tmp;
	int		t;
	int		i;

	i = 0;
	t = -1;
	if (!(tmp = (char**)ft_memalloc(sizeof(char*) * sh_count_b(str) + 1)))
		return (NULL);
	while (str[i])
	{
		sh_squote(str, &i);
		if (str[i])
		{
			i = sh_escape(str, i);
			if (str[i] && !(tmp[++t] = sh_norme(str, &i)))
			{
				ft_strtabdel(tmp);
				return (NULL);
			}
		}
		str[i] ? i++ : 0;
	}
	tmp[++t] = NULL;
	return (tmp);
}
