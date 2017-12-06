/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:54:56 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/06 10:13:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*sh_hist_line(char *line, char *gnl)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(line, gnl);
	if (tmp)
		ft_strdel(&tmp);
	if (!line)
		ft_error("Warning", "History not totally recoverded", NULL);
	if (line[0] && line[ft_strlen(line) - 1] == '\\'
			&& (!line[1] || line[ft_strlen(line) - 2] != '\\'))
		line[ft_strlen(line) - 1] = '\n';
	return (line);
}

static t_line	*sh_hist_create(t_line *hist, char **line)
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

static t_line	**sh_hist_gnl(t_line **hist, int fd)
{
	char	*line;
	char	*gnl;
	int		ret;

	line = NULL;
	gnl = NULL;
	while ((ret = get_next_line(fd, &gnl)) > 0)
	{
		if (!(line = sh_hist_line(line, gnl)))
			return (hist);
		if (!gnl[0] || !line[0] || line[ft_strlen(line) - 1] != '\n')
			if (!((*hist) = sh_hist_create((*hist), &line)))
				return (hist);
		free(gnl);
	}
	line ? free(line) : 0;
	if (ret < 0)
		ft_error("Warning", "History not totally recovered", NULL);
	return (hist);
}

t_line			*sh_hist_read(void)
{
	t_line		**hist;
	t_line		*new;
	int			fd;

	if (!(hist = sh_ghist()))
		return (NULL);
	sh_hist_del();
	if ((fd = open(sh_getvar("HISTFILE"), O_RDONLY | O_CREAT,
		S_IRUSR | S_IWUSR)) >= 0)
	{
		sh_hist_gnl(hist, fd);
		close(fd);
	}
	if (!(new = sh_hline_new("", *hist)))
		return (NULL);
	if (*hist)
	{
		(*hist)->down = new;
		*hist = (*hist)->down;
	}
	else
		*hist = new;
	return (*hist);
}
