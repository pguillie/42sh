/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:34:28 by pbourlet          #+#    #+#             */
/*   Updated: 2017/11/21 13:50:08 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ntoken_del(t_token **exp, int i)
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

t_token	*sh_word_split(t_token **exp)
{
	t_token *suivant;
	t_token *cur;
	char	**tab;
	char	*tmp2;
	int		cat;
	int		i;

	cur = *exp;
	tmp2 = NULL;
	suivant = (*exp)->next;
	cur->next = NULL;
	tab = NULL;
	if (!(tab = ft_split_allwhite((*exp)->lexeme)))
	{
		(*exp)->next = suivant;
		return (*exp);
	}
	i = 0;
	if ((tmp2 = ft_strdup(tab[i++])))
	{
		free(cur->lexeme);
		cur->lexeme = tmp2;
		cat = tab[i] && tab[i][0] == '-' ? OPT : ARG;
		while (tab[i])
		{
			tmp2 = ft_strdup(tab[i]);
			if (!tmp2 || sh_token_new(&(cur->next), tmp2, cat) < 0)
			{
				tmp2 ? free(tmp2) : 0;
				ft_strtabdel(tab);
				sh_ntoken_del(&((*exp)->next), i);
				(*exp)->next = suivant;
				return (*exp);
			}
			cur = cur->next;
			i++;
		}
	}
	cur->next = suivant;
	ft_strtabdel(tab);
	return (*exp);
}
