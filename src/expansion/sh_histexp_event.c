/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:03:58 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/03 17:02:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_histexp_event_error(char *str, int i)
{
	str[i] = 0;
	return (ft_error(SHELL, str, "Event not found"));
}

static char	*sh_histexp_event_digit(char *str, int *i, int j, t_line *hist)
{
	char	*res;
	int		offset;

	offset = 0;
	res = NULL;
	if (str[*i] == '!' && (*i)++)
	{
		if (!(res = sh_histexp_line(hist, -1)))
			return (NULL);
	}
	else if (ft_isdigit(str[*i]) || (str[*i] == '-' && (*i)++))
	{
		while (ft_isdigit(str[*i]))
			offset = offset * 10 + str[(*i)++] - '0';
		if (str[j] == '-')
			offset *= -1;
		if (!(res = sh_histexp_line(hist, offset)))
			return (NULL);
	}
	return (res);
}

static int	sh_histexp_etest(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == ':' || c == '^'
			|| c == '$' || c == '*');
}

static char	*sh_histexp_event_searching(char *str, int *i, int j, t_line *hist)
{
	char	*res;
	char	**wmatch;
	int		t;
	char	save;

	res = NULL;
	wmatch = sh_wmatch();
	while (str[*i] && str[*i] != '?')
		(*i)++;
	if (!str[*i])
		(*i)--;
	if ((res = sh_histexp_search(str + j, *i - j, hist)))
	{
		t = 0;
		while (res[t] && res[t] != '\t' && res[t] != ' ' && res[t] != '\n')
			t++;
		save = res[t];
		res[t] = '\0';
		*wmatch ? free(*wmatch) : 0;
		*wmatch = ft_strdup(res);
		res[t] = save;
		*i += str[*i] == '?' ? 1 : 0;
	}
	return (res);
}

int			sh_histexp_event(char *s, int i, char **exp, t_line *hist)
{
	int		offset;
	int		j;

	if (!s[i])
		return (0);
	j = ++i;
	offset = 0;
	if ((!s[i] || sh_histexp_etest(s[i])) && (offset = -1))
		;
	else if (s[i] == '!' || (ft_isdigit(s[i]) || s[i] == '-'))
		*exp = sh_histexp_event_digit(s, &i, j, hist);
	else if (s[i] == '#')
		*exp = ft_strsub(s, 0, i++ - 1);
	else if (s[i] == '?' && i++)
		*exp = sh_histexp_event_searching(s, &i, j, hist);
	else
	{
		while (s[i] && !sh_histexp_etest(s[i]) && s[i] != '!')
			i++;
		*exp = sh_histexp_search(s + j, i - j, hist);
	}
	if (!*exp && offset != -1)
		return (sh_histexp_event_error(s + j - 1, i - j + 1));
	ft_memmove(s + j - 1, s + i, ft_strlen(s + i) + 1);
	return (0);
}
