/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:42:40 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 21:59:39 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_hist_r(char *file)
{
	int		fd[2];
	int		i;
	char	*line;

	if ((fd[0] = open(sh_getvar("HISTFILE"), O_WRONLY | O_APPEND | O_CREAT,
		S_IRUSR | S_IWUSR)) < 0)
		return (1);
	if ((fd[1] = open(file, O_RDONLY | S_IRUSR | S_IWUSR)) < 0)
	{
		close(fd[0]);
		return (1);
	}
	while (get_next_line(fd[1], &line) > 0)
	{
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i])
			ft_putendl_fd(line, fd[0]);
		free(line);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}
