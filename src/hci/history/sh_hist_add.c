/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:00:42 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/03 16:04:18 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_hist_add2(int *fd, char *str[])
{
	while (get_next_line(fd[0], &str[0]) > 0)
	{
		if (str[1])
		{
			write(fd[1], str[1], ft_strlen(str[1]));
			write(fd[1], "\n", 1);
			free(str[1]);
		}
		str[1] = str[0];
	}
	free(str[0]);
	free(str[1]);
	close(fd[0]);
}

int			sh_hist_add(char **av, int t)
{
	int		fd[2];
	char	*str[2];
	int		i;

	if ((fd[0] = open(sh_getvar("HISTFILE"), O_RDONLY)) < 0)
		return (-1);
	if ((fd[1] = open(".42sh_tmp", O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR)) < 0)
	{
		close(fd[0]);
		return (-1);
	}
	str[1] = NULL;
	sh_hist_add2(fd, str);
	i = 0;
	while (av[i])
	{
		write(fd[1], av[i], ft_strlen(av[i]));
		write(fd[1], av[i + 1] ? " " : "\n", 1);
		i++;
	}
	close(fd[1]);
	t = 0;
	rename(".42sh_tmp", sh_getvar("HISTFILE"));
	return (0);
}
