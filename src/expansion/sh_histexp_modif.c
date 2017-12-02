/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histexp_modif.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:31:38 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 17:42:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_histexp_error(char *str, int i)
{
	str[i] = 0;
	return (ft_error(SHELL, str, "Illegal modifier"));
}

static char	*sh_histexp_path(char *exp, char c)
{
	int		i[2];

	i[0] = 0;
	i[1] = -1;
	while (exp[i[0]])
		if (exp[i[0]++] == '/')
			i[1] = i[0] - 1;
	if (i[1] < 0)
		return (ft_strdup(exp));
	if (c == 'h')
		exp[i[1]] = 0;
	else
		ft_memmove(exp, exp + i[1] + 1, ft_strlen(exp + i[1]));
	return (ft_strdup(exp));
}

static char	*sh_histexp_suff(char *exp, char c)
{
	int		i[2];

	i[0] = 0;
	i[1] = -1;
	while (exp[i[0]])
		if (exp[i[0]++] == '.')
			i[1] = i[0] - 1;
	if (i[1] < 0)
		return (ft_strdup(exp));
	if (c == 'r')
		exp[i[1]] = 0;
	else
		ft_memmove(exp, exp + i[1] + 1, ft_strlen(exp + i[1]));
	return (ft_strdup(exp));
}

static int	sh_histexp_mod2(char *str, int *i, char **exp, int j)
{
	char	*new;

	new = NULL;
	if (str[*i] == 'h' || str[*i] == 't')
		new = sh_histexp_path(*exp, str[(*i)++]);
	else if (str[*i] == 'r' || str[*i] == 'e')
		new = sh_histexp_suff(*exp, str[(*i)++]);
	else if (str[*i] == 'q' || str[*i] == 'x')
		new = sh_histexp_quote(*exp, str[(*i)++]);
	else if ((str[*i] == 'g' || str[*i] == 'a')
			&& (str[*i + 1] == 's' || str[*i + 1] == '&') && (*i)++)
		new = sh_histexp_sub(*exp, str, i, 1);
	else if (str[*i] == 's' || str[*i] == '&')
		new = sh_histexp_sub(*exp, str, i, 0);
	if (!new)
		return (sh_histexp_error(str + j + 1, *i - j));
	free(*exp);
	*exp = new;
	return (0);
}

int			sh_histexp_modif(char *str, int i, char **exp, int *b)
{
	int			j;

	if (str[i] != ':')
		return (0);
	j = i++;
	if (str[i] == 'p' && i++)
		*b = 2;
	else if (sh_histexp_mod2(str, &i, exp, j))
		return (1);
	ft_memmove(str + j, str + i, ft_strlen(str + i) + 1);
	return (0);
}
