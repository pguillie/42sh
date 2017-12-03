/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:02:26 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/03 16:06:25 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_insert(t_line *line, char *exp, int i)
{
	char	*res;
	int		len;

	len = ft_strlen(exp);
	res = NULL;
	if (line->used + ft_strlen(exp) >= line->capacity)
	{
		line->capacity += BUFF_SIZE * ((len / BUFF_SIZE) + 1);
		if (!(line->str = ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + i + len, line->str + i,
			ft_strlen(line->str + i) + 1);
	ft_strncpy(line->str + i, exp, len);
	line->used += len;
	return (0);
}

int			sh_hist_exp(t_line *line, int ret)
{
	char	*exp;
	int		i;
	int		b;

	i = 0;
	b = 0;
	printf( "# history expansion\n" );
	while ((i = sh_histexp_id(line->str, i)) >= 0 && !g_signal)
	{
		printf( "  # occurence found (%d)\n", i );
		b = b ? b : 1;
		exp = NULL;
		if (sh_histexp_event(line->str, i, &exp, line))
			return (-42);
		printf( "   - event: \"%s\"\n", exp );
		if (sh_histexp_word(line->str, i, &exp))
			return (-42);
		printf( "   - word:  \"%s\"\n", exp );
		if (sh_histexp_modif(line->str, i, &exp, &b))
			return (-42);
		printf( "   - modif: \"%s\"\n", exp );
		if (exp)
			sh_insert(line, exp, i);
		exp ? free(exp) : 0;
	}
	printf( "# end of history expansion\n" );
	if (g_signal)
		return (-1);
	b ? ft_putstr(line->str) : 0;
	return (b > 1 ? -42 : ret);
}
