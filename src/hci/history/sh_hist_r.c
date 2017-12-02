/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:42:40 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/02 17:17:40 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    sh_hist_r(char *file)
{
    // int fd;
    // t_list **hist
    //
    // if (fd = open(sh_getvar("HISTFILE"), O_RDONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR) < 0)
    //     return ;
    sh_hist_w(file);
}
