/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tab_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:51:23 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/07 11:57:53 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_norminette(t_line *line, t_coord **coord, t_tc tc, char *array[])
{
	size_t	size;
	int		disp;
	char	ans;

	size = 0;
	while (array[size])
		size += 1;
	sh_move_cur(line->cur, line->used, *coord, tc);
	if ((disp = 1) && size > 100)
	{
		ft_printf("\nDisplay all %d possibilities? (y or n)", size);
		ans = 0;
		while (ans != 'y' && ans != 'n' && ans != 127 && ans != ' '
				&& g_signal != SIGINT)
			read(0, &ans, 1);
		if (ans == 'n' || ans == 127)
			disp = 0;
	}
	g_signal != SIGINT ? write(1, "\n", 1) : 0;
	if (disp && g_signal != SIGINT)
	{
		array = ft_strtab_sort(array);
		ft_strtab_disp(array);
	}
	return (DISP_FULL);
}

int			sh_tab_multi(t_line *line, t_coord **coord, t_tc tc, char *array[])
{
	char	occ[PATH_SIZE];
	size_t	i;
	size_t	j;

	ft_strncpy(occ, array[1], PATH_SIZE);
	i = 2;
	while (array[i] && occ[0])
	{
		j = 0;
		while (j < PATH_SIZE && occ[j] && occ[j] == array[i][j])
			j++;
		ft_strclr(occ + j);
		i += 1;
	}
	if (ft_strlen(occ) > ft_strlen(array[0]))
		return (sh_tab_ins(line, coord, tc, occ + ft_strlen(array[0])));
	else
		return (sh_norminette(line, coord, tc, array + 1));
}
