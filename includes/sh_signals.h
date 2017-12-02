/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:26 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 21:00:27 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_SIGNALS_H
# define SH_SIGNALS_H

# include "shell.h"
# include <signal.h>
# include <errno.h>

int		g_signal;

void	sh_catch_signals(void);
void	sh_dfl_sig(void);

#endif
