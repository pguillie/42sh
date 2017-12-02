/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:23:00 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 21:32:13 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_hist_del_one_two(char *str[], int *fd, int *i, int pos)
{
	while (get_next_line(fd[0], &str[0]) > 0)
	{
		if (str[1])
		{
			if (*i != pos - 1)
				ft_putendl_fd(str[1], fd[1]);
			free(str[1]);
			*i += 1;
		}
		str[1] = str[0];
	}
}

static int	sh_hist_del_one(int pos)
{
	int		fd[2];
	char	*str[2];
	char	*tmp;
	int		i;

	i = 0;
	if ((fd[0] = open(sh_getvar("HISTFILE"), O_RDONLY)) < 0)
		return (-1);
	if ((fd[1] = open(".42sh_tmp", O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR)) < 0)
		return (close(fd[0]) - 1);
	str[1] = NULL;
	sh_hist_del_one_two(str, fd, &i, pos);
	if (i < pos || pos == 0)
	{
		tmp = ft_itoa(pos);
		ft_error("history", tmp, "out of range");
		free(tmp);
	}
	free(str[0]);
	close(fd[0]);
	close(fd[1]);
	rename(".42sh_tmp", sh_getvar("HISTFILE"));
	return (0);
}

static int	sh_hist_disp2(int k, int *i, t_line *h)
{
	struct tm	*tm;
	char		s[128];
	char		*t;

	while (h->down)
	{
		if (!k || i[0] > i[1] - k)
		{
			ft_printf("%5d ", i[0]);
			if ((t = sh_getvar("HISTTIMEFORMAT")))
			{
				if (!(tm = localtime((time_t*)&(h->timestamp))))
					return (-1);
				if (strftime(s, 128, t, tm) == 0)
					return (-1);
				ft_putstr(s);
			}
			ft_putendl(h->str);
		}
		h = h->down;
		i[0]++;
	}
	return (0);
}

static int	sh_hist_disp(int k)
{
	t_line		*h;
	int			i[2];

	if (!(h = sh_hist_read()))
		return (-1);
	i[1] = 0;
	while (h->up && ++i[1])
		h = h->up;
	i[0] = 1;
	return (sh_hist_disp2(k, i, h));
}

int			sh_history(char **av)
{
	char	opt[7];
	int		i;
	int		j;
	int		ret;

	if ((i = sh_history_opt(av, opt)) < 0)
		return (1);
	j = 0;
	ret = 0;
	while (opt[j])
	{
		if (opt[j] == 's')
			sh_hist_add(av + i, 0);
		else if (opt[j] == 'r' && av[i])
			ret = sh_hist_r(av[i]);
		else if (opt[j] == 'w' && av[i])
			sh_hist_w(av[i]);
		else if (opt[j] == 'c')
			sh_hist_clear();
		else if (opt[j] == 'd')
			sh_hist_del_one(ft_atoi(av[i]));
		j++;
	}
	j == 0 ? sh_hist_disp(ft_atoi(av[i])) : 0;
	return (ret);
}
