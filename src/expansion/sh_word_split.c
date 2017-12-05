/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:34:28 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/05 06:28:01 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_ntoken_del(t_token **exp, int i)
{
	t_token *cur;

	cur = NULL;
	while (i-- - 1)
	{
		cur = *exp;
		*exp = (*exp)->next;
		free(cur->lexeme);
		free(cur);
	}
	return (0);
}

static int	sh_norme(t_token **exp, t_token **lst, char **tab, int i)
{
	char	*tmp;
	int		cat;

	cat = tab[i] && tab[i][0] == '-' ? OPT : ARG;
	while (tab[i])
	{
		tmp = ft_strdup(tab[i]);
		if (!tmp || sh_token_new(&(lst[0]->next), tmp, cat) < 0)
		{
			tmp ? free(tmp) : 0;
			ft_strtabdel(tab);
			sh_ntoken_del(&((*exp)->next), i);
			(*exp)->next = lst[1];
			return (-1);
		}
		lst[0] = lst[0]->next;
		i++;
	}
	return (0);
}

t_token		*sh_word_split(t_token **exp)
{
	t_token	*lst[2];
	char	**tab;
	char	*tmp;
	int		i;

	lst[0] = *exp;
	tmp = NULL;
	lst[1] = (*exp)->next;
	if (!(tab = ft_split_allwhite((*exp)->lexeme)) || !tab[0])
	{
		tab ? free(tab) : 0;
		return (*exp);
	}
	lst[0]->next = NULL;
	i = 0;
	if ((tmp = ft_strdup(tab[i++])))
	{
		free(lst[0]->lexeme);
		lst[0]->lexeme = tmp;
		if (sh_norme(exp, lst, tab, i) < 0)
			return (*exp);
	}
	lst[0]->next = lst[1];
	ft_strtabdel(tab);
	return (*exp);
}
