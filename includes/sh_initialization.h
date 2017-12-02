/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_initialization.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:22 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 22:39:33 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_INITIALIZATION_H
# define SH_INITIALIZATION_H

void	sh_init_loop(t_token **lexer, t_cmd ****list, int **op);
int		sh_init_termcaps(t_tc *init);
int		sh_init_var(void);
int		sh_init(t_tc *init);

#endif
