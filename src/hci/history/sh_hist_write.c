/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:55:18 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/05 00:48:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hwrite(char *line, int fd, int eol)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1])
			ft_putchar_fd('\\', fd);
		if (line[i])
			ft_putchar_fd(line[i++], fd);
	}
	if (eol)
		ft_putchar_fd('\n', fd);
}

int		sh_hist_write(char *line, char *last)
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
		sh_hwrite(line, fd, 0);
		close(fd);
	}
	return (0);
}
