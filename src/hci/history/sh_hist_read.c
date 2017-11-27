/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:35:33 by mdescamp          #+#    #+#             */
/*   Updated: 2017/11/27 10:00:35 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		sh_get_history(void)
{
	char			*dir;
	struct passwd	*passwd;
	int				fd;

	// if (!(dir = sh_getvar("HISTFILE")))
		if (!(dir = ft_strdup("./history"))) //sh_getvar("HOME")))
		{
			passwd = getpwuid(getuid());
			dir = ft_strjoin(passwd->pw_dir, HISTFILE);
		}
	fd = open(dir, O_CREAT | O_RDONLY, 0644);
	free(dir);
	return (fd);
}

static int		sh_hist_fill(int fd)
{
	char	*buff;
	char	*tmp;

	while (get_next_line(fd, &buff) > 0)
	{
		// if (t != NULL && buff[0] != '#')
			// sh_hist_add(buff);
		if (buff[0] == '#')
		{
			tmp = buff;
			while (get_next_line(fd, &buff) > 0 && buff[0] == '#')
			{
				free(tmp);
				tmp = buff;
				free(buff);
			}
			sh_hist_add(buff);
			free(tmp);
		}
		else
			sh_hist_add(buff);
		free(buff);
	}
	return (1);
}

t_hist	**sh_hist_read(void)
{
	t_hist	**state;
	int		size;
	int		fd;

	if (!(state = global_hist()))
		return (NULL);
	if (!(*state = (t_hist*)ft_memalloc(sizeof(t_hist))))
		return (NULL);
	// if (sh_getvar("HISTSIZE"))
		//size = ft_atoi(sh_getvar("HISTSIZE"));
	// else
		size = ft_atoi("10");//HISTSIZE
	if (!((*state)->entry = (t_entry*)ft_memalloc(sizeof(t_entry) * size + 1)))
		return (NULL);
	(*state)->size = size;
	(*state)->length = 0;
	(*state)->offset = sh_hist_size();
	fd = sh_get_history();
	if (!(sh_hist_fill(fd)))
		return (NULL);
	close(fd);
	return (state);
}

/*int				main(void)
{
	t_state	**state;

	state = NULL;
	if (!(state = sh_init_hist(NULL)))//sh_getvar("HISTTIMEFORMAT")
		return (1);
	disp_hist_tmp();
	printf("END\n");
	sh_hist_del("1");
	printf("END2\n");
	disp_hist_tmp();
	sh_hist_add("test", time(NULL));
	disp_hist_tmp();
	sh_hist_disp();
	sh_hist_write();
	// while (1)
	// 	;
	return (1);
}
*/
