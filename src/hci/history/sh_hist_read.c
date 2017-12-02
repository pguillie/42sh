/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:54:56 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 22:57:41 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_hist_line(char *line, char *gnl)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(line, gnl);
	if (tmp)
		ft_strdel(&tmp);
	if (!line)
		ft_error("Warning", "History not totally recoverded", NULL);
	if (line[0] && line[ft_strlen(line) - 1] == '\\')
		line[ft_strlen(line) - 1] = '\n';
	return (line);
}

t_line	*sh_hist_create(t_line *hist, char **line)
{
	t_line	*new;

	if (!(new = sh_hline_new(*line, hist)))
		ft_error("Warning", "History not totally recovered", NULL);
	ft_strdel(line);
	if (hist)
	{
		hist->down = new;
		hist = hist->down;
	}
	else
		hist = new;
	return (hist);
}

t_line	*sh_hist_gnl(int fd)
{
	t_line	**hist;
	char	*line;
	char	*gnl;
	int		ret;

	line = NULL;
	gnl = NULL;
	if (!(hist = sh_ghist()))
		return (NULL);
	printf("hist: %p\n", *hist);
	while ((ret = get_next_line(fd, &gnl)) > 0)
	{
		if (!(line = sh_hist_line(line, gnl)))
			return ((*hist));
		if (!gnl[0] || !line[0] || line[ft_strlen(line) - 1] != '\n')
		{
			if (!((*hist) = sh_hist_create((*hist), &line)))
				return ((*hist));
		}
		free(gnl);
	}
	if (ret < 0)
		ft_error("Warning", "History not totally recovered", NULL);
	return ((*hist));
}

t_line	*sh_hist_read(void)
{
	t_line			*hist;
	t_line			*new;
	int				fd;

	fd = open(sh_getvar("HISTFILE"), O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
		return (NULL);
	hist = sh_hist_gnl(fd);
	close(fd);
	if (!(new = sh_hline_new("", hist)))
		return (NULL);
	if (hist)
	{
		hist->down = new;
		hist = hist->down;
	}
	else
		hist = new;
	return (hist);
}
