/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tab_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:51:25 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/07 16:15:18 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_tab_append(char **array[], char *occ, int c)
{
	char	**new;
	size_t	i;

	i = 1;
	if (*array)
		while ((*array)[i])
			if (ft_strequ((*array)[i++], occ))
				return ;
	if ((new = (char**)ft_memalloc(sizeof(char*) * (i + 2))))
	{
		if ((new[i] = ft_strnew(ft_strlen(occ) + 1)))
		{
			ft_strcpy(new[i], occ);
			c ? ft_strncat(new[i], "/", 1) : 0;
			while (i--)
				new[i] = (*array)[i];
			free(*array);
			*array = new;
		}
		else
			free(new);
	}
}

static void	sh_tab_norminette(char path[], char *dir, char *fil)
{
	ft_strncpy(path, dir, PATH_SIZE);
	ft_strlcat(path, "/", PATH_SIZE);
	ft_strlcat(path, fil, PATH_SIZE);
}

static void	sh_tab_open(char **array[], char *dir, int cat)
{
	DIR				*dirp;
	struct dirent	*de;
	struct stat		buf;
	char			path[PATH_SIZE];
	size_t			len;

	if ((dirp = opendir(dir)))
	{
		len = ft_strlen(*array[0]);
		while ((de = readdir(dirp)))
		{
			if (ft_strnequ(*array[0], de->d_name, len)
					&& !ft_strequ(de->d_name, "..")
					&& !ft_strequ(de->d_name, "."))
			{
				sh_tab_norminette(path, dir, de->d_name);
				if (stat(path, &buf) == 0
						&& (cat != CMD || S_ISDIR(buf.st_mode)
							|| S_IXUSR & buf.st_mode))
					sh_tab_append(array, de->d_name, S_ISDIR(buf.st_mode));
			}
		}
		closedir(dirp);
	}
}

char		**sh_tab_find(char *array[], char *dir, int category)
{
	char	**path;
	size_t	i;

	if (category == CMD && ft_strequ(dir, "."))
	{
		i = 0;
		path = NULL;
		if (!(path = sh_varsplit(sh_getvar("PATH"))))
			return (NULL);
		while (path[i])
		{
			sh_tab_open(&array, path[i], category);
			i += 1;
		}
		ft_strtabdel(path);
		sh_tab_builtin(&array);
	}
	else
		sh_tab_open(&array, dir, category);
	return (array);
}
