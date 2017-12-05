/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:23:00 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/05 02:53:49 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_hist_w(char *file)
{
	t_line	*h;
	int		fd;

	if (!(h = sh_hist_read()))
		return (-1);
	if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return (-1);
	while (h->up)
		h = h->up;
	while (h)
	{
		sh_hwrite(h->str, fd, h->down ? 1 : 0);
		h = h->down;
	}
	return (0);
}

static int	sh_hist_del_one(char *pos)
{
	t_line	*h;
	int		fd;
	int		i;
	int		p;

	if (!(h = sh_hist_read()))
		return (-1);
	if ((fd = open(sh_getvar("HISTFILE"), O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IWUSR)) < 0)
		return (-1);
	while (h->up)
		h = h->up;
	i = 1;
	p = ft_atoi(pos);
	while (h)
	{
		if (i != p)
			sh_hwrite(h->str, fd, h->down ? 1 : 0);
		h = h->down;
		i++;
	}
	if (!p || i - 1 <= p)
		return (ft_error(SHELL, pos, "history position out of range"));
	return (0);
}

static void	sh_hist_clear(void)
{
	int		fd;

	if ((fd = open(sh_getvar("HISTFILE"), O_TRUNC)) >= 0)
		close(fd);
}

static int	sh_hist_disp(char *str)
{
	t_line		*h;
	int			k;
	int			i[2];

	k = 0;
	if (str && ft_isnumber(str) == 0)
		return (ft_error(SHELL, str, "numeric argument required"));
	if (str && (k = ft_atoi(str)) == 0)
		return (0);
	if (!(h = sh_hist_read()))
		return (-1);
	i[1] = 0;
	while (h->up && ++i[1])
		h = h->up;
	i[0] = 1;
	while (h->down)
	{
		if (!k || i[0] > i[1] - k)
			ft_printf("%5d %s\n", i[0], h->str);
		h = h->down;
		i[0]++;
	}
	return (0);
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
		if (opt[j] == 's' && av[i])
			sh_hist_add();
		else if (opt[j] == 'r' && av[i])
			ret = sh_hist_r(av[i]);
		else if (opt[j] == 'w' && av[i])
			sh_hist_w(av[i]);
		else if (opt[j] == 'c')
			sh_hist_clear();
		else if (opt[j] == 'd')
			sh_hist_del_one(av[i]);
		j++;
	}
	j == 0 ? sh_hist_disp(av[i]) : 0;
	return (ret);
}
