/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:28:18 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/29 16:54:03 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		sh_get_history(void)
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
	fd = open(dir, O_CREAT | O_WRONLY | O_TRUNC);
	return (fd);
}

void			sh_hist_write(void)
{
	t_hist	**state;
	int		fd;
	int		i;

	i = 0;
	fd = sh_get_history();
	if (!(state = global_hist()))
		return ;
	while (i != (*state)->length && i != ft_atoi(sh_getvar("HISTFILESIZE")))
	{
		if ((*state)->entry[i].timestamp != 0)
		{
			ft_putstr_fd("#", fd);
			ft_putendl_fd(ft_itoa((*state)->entry[i].timestamp), fd);
		}
		ft_putendl_fd((*state)->entry[i].line, fd);
		i++;
	}
	close(fd);
}
