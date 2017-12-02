/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:37:48 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/02 21:37:50 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_hwrite(char *line, int fd)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1])
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(line[i++], fd);
	}
}

int			sh_hist_write(char *line, char *last)
{
	int				fd;
	int				i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && !ft_strequ(line, last))
	{
		if ((fd = open(sh_getvar("HISTFILE"), O_WRONLY | O_APPEND | O_CREAT,
						S_IRUSR | S_IWUSR)) < 0)
			return (1);
		sh_hwrite(line, fd);
		close(fd);
	}
	return (0);
}
