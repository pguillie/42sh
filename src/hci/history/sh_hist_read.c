/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:35:33 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/30 15:28:15 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_get_history(void)
{
	char			*dir;
	struct passwd	*passwd;
	int				fd;

	if (!(dir = sh_getvar("HISTFILE")))
		if (!(dir = sh_getvar("HOME")))
		{
			passwd = getpwuid(getuid());
			dir = ft_strjoin(passwd->pw_dir, HISTFILE);
		}
	fd = open(dir, O_CREAT | O_RDONLY, 0644);
	return (fd);
}

static int	sh_hist_fill(int fd)
{
	char	*buff;
	char	*tmp;

	while (get_next_line(fd, &buff) > 0)
	{
		if (buff[0] == '#')
		{
			tmp = buff;
			while (get_next_line(fd, &buff) > 0 && buff[0] == '#')
			{
				free(tmp);
				tmp = buff;
				free(buff);
			}
			sh_hist_add(buff, ft_atoi(tmp));
			free(tmp);
		}
		else
			sh_hist_add(buff, 0);
		free(buff);
	}
	return (1);
}

t_hist		**sh_hist_read(void)
{
	t_hist	**state;
	int		size;
	int		fd;

	if (!(state = global_hist()))
		return (NULL);
	if (!(*state = (t_hist*)ft_memalloc(sizeof(t_hist))))
		return (NULL);
	if (sh_getvar("HISTSIZE"))
		size = ft_atoi(sh_getvar("HISTSIZE"));
	else
		size = ft_atoi(HISTSIZE);
	if (!((*state)->entry = (t_entry*)ft_memalloc(sizeof(t_entry) * size + 2)))
		return (NULL);
	(*state)->size = size;
	(*state)->length = 0;
	(*state)->offset = 1;
	fd = sh_get_history();
	sh_hist_fill(fd);
	close(fd);
	return (state);
}
