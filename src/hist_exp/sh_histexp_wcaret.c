#include "shell.h"

char		*sh_histexp_wcaret(t_token *w, char *str, int *i)
{
	int	end;

	(*i)++;
	if (str[*i] == '*' && ++(*i))
		return (sh_histexp_new(w, 1, -1));
	else if (str[*i] == '-' && ++(*i))
	{
		if ((str[*i] == '*' || str[*i] == '$') && ++(*i))
			return (sh_histexp_new(w, 1, -1));
		else if (ft_isdigit(str[*i]))
		{
			end = 0;
			while (ft_isdigit(str[*i]))
				end = end * 10 + str[(*i)++] - '0';
			return (sh_histexp_new(w, 1, end));
		}
		else
			return (sh_histexp_new(w, 1, -2));
	}
	else
		return (sh_histexp_new(w, 1, 1));
}
