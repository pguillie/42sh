/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:32:43 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/06 13:19:26 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_histexp_sub4(char *exp, int *i, char *sub, int a)
{
	char	*new;
	int		j[3];

	j[0] = (sub[1 + a] ? a + 2 : a + 1);
	ft_memset(j + 1, 0, sizeof(int) * 2);
	while (sub[j[0] + j[1]] && sub[j[0] + j[1]] != sub[0])
		if (sub[j[0] + j[1]++] == '&')
			j[2] += (a - 1);
	if (!(new = ft_strnew(ft_strlen(exp) + j[1] + j[2] - a)))
		return (NULL);
	ft_strncat(new, exp, *i);
	j[1] = 0;
	j[2] = *i;
	while (sub[j[0] + j[1]] && sub[j[0] + j[1]] != sub[0])
	{
		if (sub[j[0] + j[1]] == '&')
		{
			ft_strncat(new, sub + 1, a);
			*i += a;
		}
		else
			new[(*i)++] = sub[j[0] + j[1]];
		j[1]++;
	}
	return (ft_strcat(new, exp + j[2] + a));
}

static void	sh_histexp_sub3(char **new, char *sub, int *i, int g)
{
	while (new[0][i[0]])
	{
		if (ft_strncmp(new[0] + i[0], sub + 1, i[1]) == 0)
		{
			if (!(new[1] = sh_histexp_sub4(new[0], i, sub, i[1])))
				break ;
			free(new[0]);
			new[0] = new[1];
			if (!g)
				break ;
		}
		else
			i[0]++;
	}
}

static char	*sh_histexp_sub2(char *exp, char *sub, int g)
{
	char	*new[2];
	int		i[2];

	new[1] = NULL;
	if (!sub || !sub[0] || !(new[0] = ft_strdup(exp)))
		return (NULL);
	ft_memset(i, 0, sizeof(int) * 2);
	while (sub[1 + i[1]] && sub[1 + i[1]] != sub[0])
		i[1]++;
	if (!i[1])
	{
		free(new[0]);
		return (NULL);
	}
	sh_histexp_sub3(new, sub, i, g);
	return (new[0]);
}

char		*sh_histexp_sub(char *exp, char *str, int *i, int global)
{
	char	**sub;
	int		j;
	int		n;

	sub = sh_hist_sub();
	if (str[(*i)++] == 's')
	{
		n = 0;
		j = *i;
		while (str[*i] && str[*i + 1] && n < 3)
		{
			if (str[*i] == str[j])
				n++;
			(*i)++;
		}
		if (*sub)
			free(*sub);
		*sub = ft_strsub(str, j, *i - j);
		if (*i <= j + 1)
			(*i)--;
	}
	return (sh_histexp_sub2(exp, *sub, global));
}
