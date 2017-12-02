/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:23:31 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/02 21:37:11 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    sh_hist_w(char *file)
{
    t_line **hist;
    int fd;

    if (!(hist = sh_ghist()) || !(*hist))
        return ;
    if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
        return ;
    while ((*hist)->up)
        (*hist) = (*hist)->up;
    while ((*hist)->down)
    {
        if ((*hist)->str)
            ft_putendl_fd((*hist)->str, fd);
        (*hist) = (*hist)->down;
    }
    close(fd);
}
