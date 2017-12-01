/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_i_search2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:20:32 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/01 17:23:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_del_char(char *str)
{
	char	*new;

	new = NULL;
	if (str)
		new = ft_strndup(str, ft_strlen(str) - 1);
	free(str);
	return (new);
}

char	*sh_ins_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (new = ft_strdup(&c));
	while (str[i])
		i++;
	if (!(new = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	new[++i] = '\0';
	free(str);
	return (new);
}

void	sh_i_prompt(char *str, t_tc *tc, int mode)
{
	if (mode == 0)
		ft_putstr("\r(reverse-i-search)'");
	else
		ft_putstr("\r(forward-i-search)'");
	tputs(tc->ce, 0, termput);
	ft_putstr(str);
	ft_putstr("\': ");
}

int		sh_cpy_hist(t_hist *hist, int *goffset, t_line **line)
{
	if (goffset[3])
	{
		(*line)->used = ft_strlen(hist->entry[goffset[2]].line);
		if (!((*line)->str = ft_strdup(hist->entry[goffset[2]].line)))
			return (-1);
	}
	else
	{
		(*line)->used = 0;
		(*line)->str = ft_strdup("");
	}
	return (0);
}

int		sh_i_strstr(char *line, char *str, int mode)
{
	if (mode == 0)
	{
		if (ft_strrstr(line, str) != NULL)
			return (1);
	}
	else if (line)
	{
		if (ft_strstr(line, str) != NULL)
			return (1);
	}
	return (0);
}
